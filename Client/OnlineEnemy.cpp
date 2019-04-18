#include "OnlineEnemy.h"



OnlineEnemy::OnlineEnemy(Logic* logic, Deck* deck, std::vector<Card>* card_stack,
	int port, bool is_hosting)
	:m_client{ port }, m_host{ port }, m_card_stack{ card_stack },
	m_logic{ logic }, m_deck{ deck }, m_is_hosting{ is_hosting }
{
}

const OnlineUser::Default_packet& OnlineEnemy::getNextMove()
{
	if (m_is_hosting)
	{
		m_host.receive_choice_information();
		return m_host.get_buffer();
	}

	else
	{
		m_client.receive_choice_information();
		return m_client.get_buffer();
	}

	// Handle the move here ? If so make the function void.
	/*
	if (!temp.uses_card)
		drawCard(m_deck->dealCard((windowSettings::windowX / 3 + m_xOffset, 125, *m_card_stack)));

	else
	{
		if (temp.card_rank != Card::SIEBEN)
	}
	*/
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