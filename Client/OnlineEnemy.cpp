#include "OnlineEnemy.h"



OnlineEnemy::OnlineEnemy(Host* host, Client* client, Logic* logic, Deck* deck, std::vector<Card>* card_stack,
	int port, bool is_hosting)
	:m_client{ client }, m_host{ host }, m_card_stack{ card_stack },
	m_logic{ logic }, m_deck{ deck }, m_is_hosting{ is_hosting }
{
	
}

void OnlineEnemy::getNextMove()
{
	if (m_is_hosting)
	{
		bool received_valid_information{ false };

		while (!received_valid_information)
			received_valid_information = m_host->receive_choice_information();

		std::cout << "killing thread\n";
		return;
	}

	else
	{
		bool received_valid_information{ false };

		while (!received_valid_information)
			received_valid_information = m_client->receive_choice_information();

		std::cout << "killing thread\n";
		return;
	}
}

const int OnlineEnemy::getHandSize()
{
	return m_enemyHand.size();
}

void OnlineEnemy::dealCard(int cardToDeal)
{
	std::cout << "Gegner: " << m_enemyHand[cardToDeal] << " -> " << m_card_stack->back() << "\n\n";
	m_enemyHand[cardToDeal].setTexture();
	std::swap(m_enemyHand[cardToDeal], m_enemyHand.back());
	m_card_stack->push_back(m_enemyHand.back());
	m_enemyHand.pop_back();
}

void OnlineEnemy::drawCard(const Card &card)
{
	m_enemyHand.push_back(card);
	std::cout << "Gegner: Karte gezogen\n\n";

	std::array<std::string, 6> temp;

	for (unsigned int i{ 0 }; i < m_logic->m_myFeed.size(); ++i)
	{
		temp[i] = m_logic->m_myFeed[i];
	}

	m_logic->m_myFeed[0] = "Gegner: Karte gezogen";

	for (unsigned int i{ 0 }; i < m_logic->m_myFeed.size() - 1; ++i)
	{
		m_logic->m_myFeed[i + 1] = temp[i];
	}
}