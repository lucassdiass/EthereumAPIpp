/*
 * EthereumQuery.cpp
 *
 *  Created on: 17 de fev de 2021
 *      Author: root
 */



#include "EthereumAPIpp.hpp"
#include <nlohmann/json.hpp>

using namespace Ethereum;
using namespace nlohmann;
using namespace APIdata;

std::string ETHEREUM::ProtolVersion()
{
	json object;
	APIdata::Result result;
	object["jsonrpc"]= "2.0";
	object["method"]= "eth_protocol_version";
	object["params"]= nlohmann::detail::value_t::null;
	object["id"]=67;

	if(Configure(&result, object))
	{
			return result.ResultStr;
	}
	throw std::runtime_error{"Error in ProtolVersion"};
}

bool ETHEREUM::Syncing()
{
	json object;
	APIdata::Result result;
	object["jsonrpc"]="2.0";
	object["method"]="eth_syncing";
	object["params"]=nlohmann::detail::value_t::null;
	object["id"]=1;

	if(Configure(&result, object))
	{
		return result.ResultBool;
	}

	throw std::runtime_error{"Error in Syncing"};
}

std::string ETHEREUM::Coinbase()
{
	json object;
	APIdata::Result result;
	object["jsonrpc"]="2.0";
	object["method"]="eth_coinbase";
	object["params"]=nlohmann::detail::value_t::null;
	object["id"]=64;

	if(Configure(&result, object))
	{
		return result.ResultStr;
	}

	throw std::runtime_error{"Error in Coinbase"};
}

bool ETHEREUM::Mining()
{
	json object;
	APIdata::Result result;
	object["jsonrpc"]="2.0";
	object["method"]="eth_mining";
	object["params"]=nlohmann::detail::value_t::null;
	object["id"]=71;

	if(Configure(&result, object))
	{
		return result.ResultBool;
	}

	throw std::runtime_error{"Error in Mining"};
}
std::string ETHEREUM::HashRate()
{
	json object;
	APIdata::Result result;
	object["jsonrpc"]="2.0";
	object["method"]="eth_hashrate";
	object["params"]=nlohmann::detail::value_t::null;
	object["id"]=71;

	if(Configure(&result, object))
	{
		return result.ResultStr;
	}

	throw std::runtime_error{"Error in HashRate"};
}

std::string ETHEREUM::GasPrice()
{
	json object;
	APIdata::Result result;
	object["jsonrpc"]="2.0";
	object["method"]="eth_gasPrice";
	object["params"]=nlohmann::detail::value_t::null;
	object["id"]=73;

	if(Configure(&result, object))
	{
		return result.ResultStr;
	}

	throw std::runtime_error{"Error in GasPrice"};
}
APIdata::Result ETHEREUM::EstimateGas(Transaction transaction)
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
		object["params"]={req};
		object["id"]=1;

		if(Configure(&result, object))
		{
			return result;
		}
	}
	throw std::runtime_error{"Error in EstimateGas"};
}

std::string ETHEREUM::BlockNumber()
{
	json object;
	APIdata::Result result;
	object["jsonrpc"]="2.0";
	object["method"]="eth_blockNumber";
	object["params"]=nlohmann::detail::value_t::null;
	object["id"]=83;

	if(Configure(&result, object))
	{
		return result.ResultStr;
	}

	throw std::runtime_error{"Error in BlockNumber"};
}
