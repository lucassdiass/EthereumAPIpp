/*
 * Net.cpp
 *
 *  Created on: 12 de fev de 2021
 *      Author: root
 */
#include "EthereumAPIpp.hpp"
#include <nlohmann/json.hpp>

using namespace Ethereum::Network;
using namespace nlohmann;
using namespace APIdata;

NET::NET(std::string URL) : URL{URL}
{

}

std::string NET::Net_version()
{
	json object;
	object["jsonrpc"]="2.0";
	object["method"]="net_version";
	object["params"]= nlohmann::detail::value_t::null;
	object["id"]=67;

	APIdata::Result result;
	if(Configure(&result, object))
	{
		return result.ResultStr;
	}
	throw std::runtime_error{"Error in net_version"};
}

bool NET::Net_listening()
{
	json object;
	CURLcode code;
	object["jsonrpc"]="2.0";
	object["method"]="net_listening";
	object["params"]= nlohmann::detail::value_t::null;
	object["id"]=67;

	APIdata::Result result;
	if(Configure(&result, object))
	{
		return result.ResultBool;
	}
	throw std::runtime_error{"Error in net_listening"};
}

std::string NET::Net_peerCount()
{
	json object;
	//CURLcode code;
	object["jsonrpc"]="2.0";
	object["method"]="net_peerCount";
	object["params"]= nlohmann::detail::value_t::null;
	object["id"]=74;
	APIdata::Result result;

	if(Configure(&result, object))
	{
		return result.ResultStr;
	}
	throw std::runtime_error{"Error in net_peerCount"};
}

bool NET::Configure(APIdata::Result*res, json object)
{
	CURLcode code;
	std::string request= object.dump();
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
		code = curl_easy_setopt(handle.get(), CURLOPT_POST, 1L);
		code = curl_easy_setopt(handle.get(), CURLOPT_HTTPHEADER, header.get());
		code = curl_easy_setopt(handle.get(), CURLOPT_WRITEDATA, (void *)res);
		code = curl_easy_setopt(handle.get(), CURLOPT_WRITEFUNCTION, Write_callback);
		curl_easy_setopt(handle.get(), CURLOPT_POSTFIELDS, request.data());
		if(curl_easy_perform(handle.get()) == CURLE_OK) {
			return true;
		}
	}
	return false;

}

size_t NET::Write_callback(char *dest, size_t size, size_t nmemb, void *userp)
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
			} else if (j.find("error:") != j.end())
			{
				wt->Error = true;
			}
		}
	}
	return buffer_size;
}
