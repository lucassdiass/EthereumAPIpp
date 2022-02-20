/*
 * EthereumAPIpp.hpp
 *
 *  Created on: 11 de fev de 2021
 *      Author: root
 */

#ifndef INTERFACEETHEREUMAPIPP_HPP_
#define INTERFACEETHEREUMAPIPP_HPP_
#include <bits/stdc++.h>
#include <nlohmann/json.hpp>

/*
 *
 * https://eth.wiki/json-rpc/API
 *
 */
namespace APIdata
{
struct Result
{
	unsigned int Id;
	std::string Jsonrpc;
	std::string ResultStr{};
	std::unordered_set<std::string> ResultSet{};
	nlohmann::json ResultObject;
	std::vector<std::string> ResultArray{};
	bool ResultBool{false};
	int ResultInt=0;
	unsigned int ResultUInt=0;
	bool Error;

};

struct RequestInformationBlockHash
{

	std::string  Block;
	bool IsFull;
};
struct Request
{
	std::string Jsonrpc;
	std::string Method;
	std::vector<std::string> Params;
	unsigned int Id;
};
struct Transaction
{
	std::string Object, Data, From, Gas, GasPrice, To, Value;
	unsigned int Nonce=0;

};


class NETIface
{
public :
	NETIface() =default;
	virtual std::string Net_version() =0;
	virtual bool Net_listening() =0;
	virtual std::string Net_peerCount() =0;
	virtual ~NETIface() = default;
};

class ETHEREUMIface
{
public :
	ETHEREUMIface() = default;
	virtual std::unordered_set<std::string> Accounts() =0;
	virtual std::string ProtolVersion() =0;
	virtual bool Syncing()  =0;
	virtual std::string Coinbase()  =0;
	virtual bool Mining() =0;
	virtual std::string HashRate() =0;
	virtual std::string GasPrice() =0;
	virtual std::string BlockNumber() =0;
	virtual Result EstimateGas(Transaction) =0;

	virtual std::string Sign(std::string address, std::string data) =0;
	virtual Result SignTransaction(Transaction, bool) =0;
	virtual Result SendTransaction(Transaction) =0;
	virtual Result SendRawTransaction(std::string  SignedTransactionData) =0;
	virtual Result Call(Transaction) =0;

	virtual Result GetBalance(std::string address, std::string tag) =0;
	virtual Result GetTransactionCount(std::string address, std::string tag) =0;
	virtual Result GetBlockTransactionCountByHash(std::string blockhash) =0;
	virtual Result GetBlockTransactionCountByNumber(unsigned int blocknumber) =0;
	virtual Result GetUncleCountByBlockHash(std::string blockhash) =0;
	virtual Result GetUncleCountByBlockNumber(unsigned int blocknumber) =0;
	virtual Result GetTransactionReceipt(std::string transcationhash ) =0;
	virtual Result GetBlockByHash(std::string , bool) =0;
	virtual Result GetBlockByNumber(unsigned int, bool) =0;
	virtual Result GetTransactionByHash(std::string blockhash) =0;
	virtual Result  compileSolidity(std::string code) =0;
	virtual ~ETHEREUMIface() = default;
};

/*
 * Classe para serializar as chamadas
 * A formatação é a  assinatura da função aplicada ao hash keccak 256 mais os parametros em hexadecimal
 * é utilizado 4 bytes do resultado do hash
 */
class SmartContractCommandIface
{
public :
	SmartContractCommandIface() =default;
	virtual std::string SerializaCallAndParams() =0;
	virtual ~SmartContractCommandIface() =default;
};

}

#endif /* INTERFACEETHEREUMAPIPP_HPP_ */
