/*
 * ETHEREUMTest.cpp
 *
 *  Created on: 19 de fev de 2022
 *      Author: Lucas Dias
 */
#include <EthereumAPIpp.hpp>
#include <gtest/gtest.h>

const std::string url{"http://127.0.0.1:8501"};

using namespace Ethereum;
class ETHEREUMTester : public testing::Test {
public:
	void InitEthereum(std::string URL)
	{
		curl_global_init(CURL_GLOBAL_DEFAULT);
		EXPECT_NO_THROW(ethereum_tester = new ETHEREUM{URL});
	}
	void FinishEthereum()
	{
		curl_global_cleanup();
		delete ethereum_tester;
		ethereum_tester = nullptr;
	}
	ETHEREUM * ethereum_tester = nullptr;
};

TEST_F(ETHEREUMTester, ConsultInvalidURLEthereum)
{
	InitEthereum("");
	EXPECT_THROW(ethereum_tester->Accounts(), std::runtime_error);
	EXPECT_THROW(ethereum_tester->ProtolVersion(), std::runtime_error);
	EXPECT_THROW(ethereum_tester->Syncing(), std::runtime_error);
	EXPECT_THROW(ethereum_tester->Coinbase(), std::runtime_error);
	EXPECT_THROW(ethereum_tester->Mining(), std::runtime_error);
	EXPECT_THROW(ethereum_tester->HashRate(), std::runtime_error);
	EXPECT_THROW(ethereum_tester->GasPrice(), std::runtime_error);
	EXPECT_THROW(ethereum_tester->BlockNumber(), std::runtime_error);

	/*
	virtual Result Sign(std::string address, std::string data) =0;
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
	 */
	FinishEthereum();
}

TEST_F(ETHEREUMTester, ConsultAccounts)
{
	InitEthereum(url);
	std::unordered_set<std::string> result;
	EXPECT_NO_THROW(result = ethereum_tester->Accounts());
	ASSERT_GT(result.size(), 0);
	FinishEthereum();
}

TEST_F(ETHEREUMTester, ConsultSyncing)
{
	InitEthereum(url);
	bool result;
	EXPECT_NO_THROW(result = ethereum_tester->Syncing());
	ASSERT_EQ(result, false);
	FinishEthereum();
}
TEST_F(ETHEREUMTester, ConsultCoinbase)
{
	InitEthereum(url);
	std::string result;
	EXPECT_NO_THROW(result = ethereum_tester->Coinbase());
	ASSERT_NE(result, std::string{});
	FinishEthereum();
}
TEST_F(ETHEREUMTester, ConsultMining)
{
	InitEthereum(url);
	bool result;
	EXPECT_NO_THROW(result = ethereum_tester->Mining());
	ASSERT_EQ(result, true);
	FinishEthereum();
}

TEST_F(ETHEREUMTester, ConsultHashRate)
{
	InitEthereum(url);
	std::string result;
	EXPECT_NO_THROW(result = ethereum_tester->HashRate());
	ASSERT_NE(result, std::string{});
	FinishEthereum();
}

TEST_F(ETHEREUMTester, ConsultGasPrice)
{
	InitEthereum(url);
	std::string result;
	EXPECT_NO_THROW(result = ethereum_tester->GasPrice());
	ASSERT_NE(result, std::string{});
	FinishEthereum();
}

TEST_F(ETHEREUMTester, ConsultBlockNumber)
{
	InitEthereum(url);
	std::string result;
	EXPECT_NO_THROW(result = ethereum_tester->BlockNumber());
	ASSERT_NE(result, std::string{});
	FinishEthereum();
}
