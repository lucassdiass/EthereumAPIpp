/*
 * EthereumAPIpp.hpp
 *
 *  Created on: 12 de fev de 2021
 *      Author: Lucas Dias
 */

#ifndef ETHEREUMAPIPP_HPP_
#define ETHEREUMAPIPP_HPP_
#include "InterfaceEthereumAPIpp.hpp"

#include <curl/curl.h>

namespace Ethereum
{
namespace Network
{
class NET : public APIdata::NETIface
{
public :
	NET(std::string URL);
	std::string  Net_version() override;
	bool  Net_listening() override;
	std::string  Net_peerCount() override;
	~NET() = default;
private :
	std::shared_ptr< CURL> handle=nullptr;
	std::string URL;
	static size_t Write_callback(char *dest, size_t size, size_t nmemb, void *userp);
	bool Configure(APIdata::Result*,nlohmann::json);
	std::shared_ptr<curl_slist> header=nullptr;
};
}

class ETHEREUM : public APIdata::ETHEREUMIface
{
public :
	ETHEREUM(std::string URL);
	/*
	 * @return Result with ResultSet
	 */
	std::unordered_set<std::string> Accounts() override;
	/*
	 * @return ReturStr
	 */
	std::string Sign(std::string address, std::string data) override;
	/*
	 * @return ReturStr
	 */
	APIdata::Result SignTransaction(APIdata::Transaction , bool) override;
	/*
	 * @return ReturStr
	 */
	APIdata::Result SendTransaction(APIdata::Transaction) override;
	/*
	 * @return ReturStr
	 */
	APIdata::Result SendRawTransaction(std::string  SignedTransactionData) override;
	/*
	 * @return protocol version ReturnStr
	 */
	std::string ProtolVersion() override;
	/*
	 *@return p ResultStr
	 */
	APIdata::Result EstimateGas(APIdata::Transaction) override;
	/*
	 *@return ResultBool
	 */
	bool Syncing() override;
	/*
	 * @return ResultSTR
	 */
	std::string Coinbase() override;
	/*
	 * @return ResultBool
	 */
	bool Mining() override;
	/*
	 * @return hash rate - ResultStr
	 */
	std::string HashRate() override;
	/*
	 * @return gas price - ResultStr
	 */
	std::string GasPrice() override;
	/*
	 * @return block number - ResultStr
	 */
	std::string BlockNumber() override;
	/*
	 * the return value of executed contract
	 * @return ReturStr
	 */
	APIdata::Result Call(APIdata::Transaction) override;
	/*
	 * @return ReturnSTR
	 */
	APIdata::Result GetBalance(std::string address, std::string tag) override;
	/*
	 * @return ReturStr
	 */
	APIdata::Result GetTransactionCount(std::string address, std::string tag) override;
	/*
	 * @return ReturStr
	 */
	APIdata::Result GetBlockTransactionCountByHash(std::string blockhash) override;
	/*
	 * @return ReturStr
	 */
	APIdata::Result GetBlockTransactionCountByNumber(unsigned int blocknumber) override;
	/*
	 * @return ReturStr
	 */
	APIdata::Result GetUncleCountByBlockHash(std::string blockhash) override;
	/*
	 * @return ReturStr
	 */
	APIdata::Result GetUncleCountByBlockNumber(unsigned int blocknumber) override;
	/*
	 * @return ResultMap
	 */
	APIdata::Result GetTransactionReceipt(std::string transcationhash ) override;
	/*
	 * @return ResultMap
	 */
	APIdata::Result GetBlockByHash(std::string blockhash, bool  isfull) override;
	/*
	 * @return ResultMap
	 */
	APIdata::Result GetBlockByNumber(unsigned int blocknumber, bool isfull) override;
	/*
	 * @return ResultMap
	 */
	APIdata::Result GetTransactionByHash(std::string blockhash) override;
	/*
	 * @return ResultMap
	 */
	APIdata::Result  compileSolidity(std::string code) override;
	~ETHEREUM() =default;
private :
	std::string URL;
	std::shared_ptr< CURL> handle=nullptr;
	std::shared_ptr<curl_slist> header=nullptr;
	static size_t Write_callback(char *dest, size_t size, size_t nmemb, void *userp);
	bool Configure(APIdata::Result*res, nlohmann::json object);
};


}

#endif /* ETHEREUMAPIPP_HPP_ */
