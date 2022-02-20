/*
 * Ethereum.cpp
 *
 *  Created on: 12 de fev de 2021
 *      Author: root
 */
#include "EthereumAPIpp.hpp"
#include <nlohmann/json.hpp>

using namespace Ethereum;
using namespace nlohmann;
using namespace APIdata;

size_t ETHEREUM::Write_callback(char *dest, size_t size, size_t nmemb, void *userp)
{
	Result *wt = (Result *)userp;
	size_t buffer_size = size*nmemb;
	std::string aux{};
	if(buffer_size)
	{
		for(int i =0;i<buffer_size;i++)
		{
			aux.push_back(dest[i]);
		}
		nlohmann::json j= nlohmann::json::parse(aux);
		if(j.size()==3)
		{
			if(j.find("id")!= j.end())
			{
				wt->Id=j["id"].get<unsigned int>();
			}
			if(j.find("jsonrpc")!= j.end())
			{
				wt->Jsonrpc=j["jsonrpc"].get<std::string>();
			}
			if(j.find("result")!= j.end())
			{
				switch(j.type())
				{
				case nlohmann::detail::value_t::array :
					wt->ResultArray=j["result"].get<std::vector<std::string>>();
					break;
				case nlohmann::detail::value_t::string :
					wt->ResultStr=j["result"].get<std::string>();
					break;
				case nlohmann::detail::value_t::boolean :
					wt->ResultBool=j["result"].get<bool>();
					break;
				case nlohmann::detail::value_t::number_integer :
					wt->ResultInt=j["result"].get<int>();
					break;
				case nlohmann::detail::value_t::object :
				{
					try
					{
						wt->ResultSet=j["result"].get<std::unordered_set<std::string>>();
					}
					catch(std::exception &e)
					{
						try
						{
							wt->ResultStr=j["result"].get<std::string>();
						}
						catch(...)
						{
							try
							{
								wt->ResultBool=j["result"].get<bool>();
							}
							catch(...)
							{
								wt->ResultObject=j["result"].get<nlohmann::json>();
							}
						}
					}
					break;
				}
				}
			}
			else if (j.find("error:") != j.end())
			{
				wt->Error = true;
			}
		}
	}
	return buffer_size;

}
bool ETHEREUM::Configure(APIdata::Result*res, nlohmann::json object)
{
	CURLcode code;
	if(!handle)
	{
		handle=std::shared_ptr<CURL>{curl_easy_init(), curl_easy_cleanup};
	}
	else
	{
		curl_easy_reset(handle.get());
	}
	code=curl_easy_setopt(handle.get(),CURLOPT_URL,URL.data());
	if(!header)
	{
		header = std::shared_ptr<curl_slist>{curl_slist_append(nullptr, "Content-Type: application/json"), curl_slist_free_all};
	}

	if(code==CURLE_OK && curl_easy_perform(handle.get())==CURLE_OK && header && header.get())
	{
		code= curl_easy_setopt(handle.get(), CURLOPT_POST, 1L);
		code = curl_easy_setopt(handle.get(), CURLOPT_HTTPHEADER, header.get());
		code = curl_easy_setopt(handle.get(), CURLOPT_WRITEDATA, (void *)res);
		code = curl_easy_setopt(handle.get(), CURLOPT_WRITEFUNCTION,Write_callback);

		std::string request = object.dump();
		curl_easy_setopt(handle.get(), CURLOPT_POSTFIELDS, request.data());
		if(curl_easy_perform(handle.get()) == CURLE_OK) {
			return true;
		}

	}
	return false;
}

std::unordered_set<std::string> ETHEREUM::Accounts()
{
	json object;
	APIdata::Result result;
	object["jsonrpc"]="2.0";
	object["method"]="eth_accounts";
	object["params"]={};
	object["id"]=1;

	if(Configure(&result, object))
	{
		return result.ResultSet;
	}
	throw std::runtime_error{"Error in Accounts"};
}

std::string ETHEREUM::Sign(std::string address, std::string data)
{
	json object;
	APIdata::Result result;
	object["jsonrpc"]="2.0";
	object["method"]="eth_sign";
	object["params"]={address, data};
	object["id"]=1;

	if(Configure(&result, object))
	{
		return result.ResultStr;
	}

	throw std::runtime_error{"Error in Sign"};
}
APIdata::Result ETHEREUM::SignTransaction(APIdata::Transaction transaction, bool iscontract )
{
	json object, req;
	APIdata::Result result;
	if(!transaction.From.empty() && !transaction.Data.empty() && (iscontract||!transaction.To.empty()) )//From is not optional
	{
		object["id"]=1;
		object["jsonrpc"]="2.0";
		object["method"]="eth_signTransaction";
		req["from"]=transaction.From;
		if(transaction.To.size())
		{
			req["to"]=transaction.To;
		}
		if(transaction.Gas.size())
		{
			req["gas"]=transaction.Gas;
		}
		if(transaction.GasPrice.size())
		{
			req["gasPrice"]=transaction.GasPrice;
		}
		if(transaction.Value.size())
		{
			req["value"]=transaction.Value;
		}
		req["data"]=transaction.Data;
		if(transaction.Nonce)
		{
			req["nonce"]=transaction.From;
		}
		object["params"]={req};

		if(Configure(&result, object))
		{
			return result;
		}

	}
	throw std::runtime_error{"Error in SignTransaction"};
}
APIdata::Result ETHEREUM::SendRawTransaction(std::string  SignedTransactionData)
{
	json object;
	APIdata::Result result;
	object["jsonrpc"]="2.0";
	object["method"]="eth_sendRawTransaction";
	object["params"]={SignedTransactionData};
	object["id"]=1;

	if(Configure(&result, object))
	{
		return result;
	}

	throw std::runtime_error{"Error in SendRawTransaction"};
}

APIdata::Result ETHEREUM::SendTransaction(APIdata::Transaction transaction)
{
	json object, req;
	APIdata::Result result;
	if(!transaction.From.empty())//From is not optional
	{
		object["jsonrpc"]="2.0";
		object["method"]="eth_sendTransaction";
		req["from"]=transaction.From;
		if(transaction.To.size())
		{
			req["to"]=transaction.To;
		}
		if(transaction.Gas.size())
		{
			req["gas"]=transaction.Gas;
		}
		if(transaction.GasPrice.size())
		{
			req["gasPrice"]=transaction.GasPrice;
		}
		if(transaction.Value.size())
		{
			req["value"]=transaction.Value;
		}
		if(transaction.Data.size())
		{
			req["data"]=transaction.Data;
		}
		if(transaction.Nonce)
		{
			req["nonce"]=transaction.Nonce;
		}
		object["params"]={req};
		object["id"]=1;

		if(Configure(&result, object))
		{
			return result;
		}

	}
	throw std::runtime_error{"Error in SendRawTransaction"};
}

ETHEREUM::ETHEREUM(std::string URL) : URL{URL}
{

}

APIdata::Result ETHEREUM::Call(APIdata::Transaction transaction)
{
	json object, req;
	APIdata::Result result;
	if(!transaction.To.empty())//To is not optional
	{
		object["jsonrpc"]="2.0";
		object["method"]="eth_call";
		req["from"]=transaction.From;
		if(transaction.To.size())
		{
			req["to"]=transaction.To;
		}
		if(transaction.Gas.size())
		{
			req["gas"]=transaction.Gas;
		}
		if(transaction.GasPrice.size())
		{
			req["gasPrice"]=transaction.GasPrice;
		}
		if(transaction.Value.size())
		{
			req["value"]=transaction.Value;
		}
		if(transaction.Data.size())//data is sha3 from signature function and params in hexadecimal with lenght of 32 bytes
		{
			req["data"]=transaction.Data;
		}
		if(transaction.Nonce)
		{
			req["nonce"]=transaction.Nonce;
		}
		object["params"]={req,"latest"};
		object["id"]=1;

		if(Configure(&result, object))
		{
			return result;
		}
	}
	throw std::runtime_error{"Error in CALL"};
}
