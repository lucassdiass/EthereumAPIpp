/*
 * EthereumETHEREUM::Get.cpp
 *
 *  Created on: 17 de fev de 2021
 *      Author: root
 */

#include "EthereumAPIpp.hpp"

using namespace Ethereum;
using namespace nlohmann;
using namespace APIdata;

APIdata::Result ETHEREUM::ETHEREUM::GetBalance(std::string address, std::string tag="latest")
{
	json object;
	APIdata::Result result;
	if(!address.empty()&& !tag.empty())
	{
		object["jsonrpc"]="2.0";
		object["method"]="eth_getBalance";
		object["params"]=std::vector<std::string>{address, tag};
		object["id"]=1;

		if(Configure(&result, object))
		{
			return result;
		}

	}
	throw std::runtime_error{"Error in ETHEREUM::Get Balance"};
}
APIdata::Result ETHEREUM::GetTransactionCount(std::string address, std::string tag="latest")
{
	json object;
	APIdata::Result result;
	if(!address.empty()&& !tag.empty())
	{
		object["jsonrpc"]="2.0";
		object["method"]="eth_getTransactionCount";
		object["params"]=std::vector<std::string>{address, tag};
		object["id"]=1;

		if(Configure(&result, object))
		{
			return result;
		}
	}
	throw std::runtime_error{"Error in Get Transaction Count"};
}

APIdata::Result ETHEREUM::GetBlockTransactionCountByHash(std::string blockhash)
{
	json object;
	APIdata::Result result;
	if(!blockhash.empty())
	{
		object["jsonrpc"]="2.0";
		object["method"]="eth_getBlockTransactionCountByHash";
		object["params"]=std::vector<std::string>{blockhash};
		object["id"]=1;

		if(Configure(&result, object))
		{
			return result;
		}

	}
	throw std::runtime_error{"Error in Get Transaction Count"};
}
APIdata::Result ETHEREUM::GetBlockTransactionCountByNumber(unsigned int blocknumber)
{
	json object;
	APIdata::Result result;
	std::ostringstream stream;
	stream << std::setw(2) << std::setfill('0') << std::hex <<blocknumber;
	object["jsonrpc"]="2.0";
	object["method"]="eth_getBlockTransactionCountByNumber";
	object["params"]=std::vector<std::string>{stream.str()};
	object["id"]=1;

	if(Configure(&result, object))
	{
		return result;
	}

	throw std::runtime_error{"Error in Get Block Transaction Count By Number"};
}
APIdata::Result ETHEREUM::GetUncleCountByBlockHash(std::string blockhash)
{
	json object;
	APIdata::Result result;
	if(blockhash.size()!=(32*2))
	{
		throw std::runtime_error{"Error in Block Hash in Get Uncle Count By Block Hash"};
	}
	object["jsonrpc"]="2.0";
	object["method"]="eth_getUncleCountByBlockHash";
	object["params"]=std::vector<std::string>{blockhash};
	object["id"]=1;

	if(Configure(&result, object))
	{
		return result;
	}

	throw std::runtime_error{"Error in Get Uncle Count By Block Hash"};
}
APIdata::Result ETHEREUM::GetUncleCountByBlockNumber(unsigned int blocknumber)
{
	json object;
	APIdata::Result result;
	std::ostringstream stream;
	stream << std::setw(2) << std::setfill('0') << std::hex <<blocknumber;
	object["jsonrpc"]="2.0";
	object["method"]="eth_getUncleCountByBlockNumber";
	object["params"]=std::vector<std::string>{stream.str()};
	object["id"]=1;

	if(Configure(&result, object))
	{
		return result;
	}

	throw std::runtime_error{"Error in Get Transaction Count"};
}

APIdata::Result ETHEREUM::GetBlockByHash(std::string blockhash, bool  isfull)
{
	json object;
	APIdata::Result result;
	RequestInformationBlockHash params;
	if(blockhash.size()==32)
	{
		params.Block=blockhash;
		params.IsFull=isfull;
		object["jsonrpc"]="2.0";
		object["method"]="eth_getBlockByHash";
		object["id"]=1;
		object["params"]={params.Block, params.IsFull};

		if(Configure(&result, object))
		{
			return result;
		}
	}

	throw std::runtime_error{"Error in Get Block By Hash"};

}
APIdata::Result ETHEREUM::GetBlockByNumber(unsigned int blocknumber, bool isfull )
{
	json object;
	APIdata::Result result;
	RequestInformationBlockHash params;
	std::ostringstream stream;
	stream << std::setw(2) << std::setfill('0') << std::hex <<blocknumber;
	params.Block=stream.str();
	params.IsFull=isfull;
	object["jsonrpc"]="2.0";
	object["method"]="eth_getBlockByNumber";
	object["id"]=1;
	object["params"]={params.Block, params.IsFull};

	if(Configure(&result, object))
	{
		return result;
	}

	throw std::runtime_error{"Error in Get Block By Number"};
}
APIdata::Result ETHEREUM::GetTransactionByHash(std::string blockhash)
{
	json object;
	APIdata::Result result;
	if(blockhash.size()!=(32*2))
	{
		throw std::runtime_error{"Error in Block Hash in Get Uncle Count By Block Hash"};
	}
	object["jsonrpc"]="2.0";
	object["method"]="eth_getTransactionByHash";
	object["params"]=std::vector<std::string>{blockhash};
	object["id"]=1;

	if(Configure(&result, object))
	{
		return result;
	}

	throw std::runtime_error{"Error in Get Uncle Count By Block Hash"};
}
APIdata::Result ETHEREUM::compileSolidity(std::string code)
{
	json object;
	APIdata::Result result;
	object["jsonrpc"]="2.0";
	object["method"]="eth_compileSolidity";
	object["params"]={code};
	object["id"]=1;

	if(Configure(&result, object))
	{
		return result;
	}
	throw std::runtime_error{"Error in compileSolidity"};
}

APIdata::Result ETHEREUM::GetTransactionReceipt(std::string transcationhash )
{
	json object;
	APIdata::Result result;
	if(transcationhash.size()!=(2+(32*2)))
	{
		throw std::runtime_error{"Error in Block Hash in Get Uncle Count By Block Hash"};
	}
	object["jsonrpc"]="2.0";
	object["method"]="eth_getTransactionReceipt";
	object["params"]={transcationhash};
	object["id"]=1;

	if(Configure(&result, object))
	{
		return result;
	}

	throw std::runtime_error{"Error in Get Uncle Count By Block Hash"};
}
