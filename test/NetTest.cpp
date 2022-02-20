/*
 * NetTest.cpp
 *
 *  Created on: 19 de fev de 2022
 *      Author: Lucas Dias
 */

#include <EthereumAPIpp.hpp>
#include <gtest/gtest.h>

const std::string url{"http://127.0.0.1:8501"};

using namespace Ethereum::Network;
class NETTester : public testing::Test {
public:
	void InitNet(std::string URL)
	{
		curl_global_init(CURL_GLOBAL_DEFAULT);
		EXPECT_NO_THROW(net_tester = new NET{URL});
	}
	void FinishNet()
	{
		curl_global_cleanup();
		delete net_tester;
		net_tester = nullptr;
	}
	NET * net_tester = nullptr;
};

TEST_F(NETTester, ConsultInvalidURL)
{
	InitNet("");
	EXPECT_THROW(net_tester->Net_version(), std::runtime_error);
	EXPECT_THROW(net_tester->Net_listening(), std::runtime_error);
	EXPECT_THROW(net_tester->Net_peerCount(), std::runtime_error);
	FinishNet();
}

TEST_F(NETTester, ConsultNetVersion)
{
	InitNet(url);
	std::string result;
	EXPECT_NO_THROW(result = net_tester->Net_version());
	ASSERT_NE(result, std::string{""});
	FinishNet();
}

TEST_F(NETTester, ConsultNetListening)
{
	InitNet(url);
	bool result;
	EXPECT_NO_THROW(result = net_tester->Net_listening());
	ASSERT_EQ(result, true);
	FinishNet();
}

TEST_F(NETTester, ConsultNetPeerCount)
{
	InitNet(url);
	std::string result;
	EXPECT_NO_THROW(result = net_tester->Net_peerCount());
	ASSERT_NE(result, std::string{});
	FinishNet();
}
