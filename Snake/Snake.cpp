#include "Snake.h"

Snake::Snake(sf::Vector2f position, sf::Uint8 length, sf::Color color, Direction dir, Control control)
	: m_Size(sf::Vector2f(10.0f, 10.0f)), m_InitLength(length)
{
	m_StartingPoint = position;
	m_Direction = dir;
	m_Control = control;
	m_CanMove = true;
	m_Color = color;
	m_GrowDelta = 0;
}

Snake::~Snake()
{
	for (auto node : m_Nodes)
		delete node;
	m_Nodes.clear();
}

sf::RectangleShape* Snake::CreateNode()
{
	auto node = new sf::RectangleShape(m_Size);
	node->setFillColor(m_Color);
	return node;
}

bool Snake::Collide(const Snake* snake)
{
	for (size_t i = 0; i < snake->m_Nodes.size(); i++)
	{
		auto rect = snake->m_Nodes[i]->getGlobalBounds();

		for (size_t j = 0; j < m_Nodes.size(); j++)
		{
			if (i != j && m_Nodes[j]->getGlobalBounds().intersects(rect))
				return true;
		}
	}

	return false;
}

void Snake::Init()
{
	auto dirVec = GetDirectionVector();

	for (size_t i = 0; i < m_InitLength; i++)
	{
		auto newNode = CreateNode();
		newNode->setPosition(sf::Vector2f(m_StartingPoint.x - dirVec.x * i,
			m_StartingPoint.y - dirVec.y * i));
		m_Nodes.push_back(newNode);
	}
}

void Snake::Input(sf::Event& events)
{
	if (!m_CanMove) return;

	if (m_Control == Control::Arrows)
	{
		switch (events.key.code)
		{
		case sf::Keyboard::Up:
			SetDirection(Direction::Up);
			break;
		case sf::Keyboard::Down:
			SetDirection(Direction::Down);
			break;
		case sf::Keyboard::Left:
			SetDirection(Direction::Left);
			break;
		case sf::Keyboard::Right:
			SetDirection(Direction::Right);
			break;
		}
	}
	else if (m_Control == Control::WSAD)
	{
		switch (events.key.code)
		{
		case sf::Keyboard::W:
			SetDirection(Direction::Up);
			break;
		case sf::Keyboard::S:
			SetDirection(Direction::Down);
			break;
		case sf::Keyboard::A:
			SetDirection(Direction::Left);
			break;
		case sf::Keyboard::D:
			SetDirection(Direction::Right);
			break;
		}
	}
}

void Snake::Update(sf::Time& delta)
{
	auto oldFrontNode = m_Nodes.front();
	auto newFrontNode = m_Nodes.back();

	newFrontNode->setFillColor(m_Color);
	newFrontNode->setPosition(oldFrontNode->getPosition() + GetDirectionVector());

	m_Nodes.push_front(newFrontNode);
	m_Nodes.pop_back();

	// GROWING
	if (m_GrowDelta > 0)
	{
		auto lastNode = m_Nodes.at(m_Nodes.size() - 1);
		auto nLastNode = m_Nodes.at(m_Nodes.size() - 2);

		float x = nLastNode->getGlobalBounds().left - lastNode->getGlobalBounds().left;
		float y = nLastNode->getGlobalBounds().top - lastNode->getGlobalBounds().top;

		auto newNode = CreateNode();
		newNode->setPosition(lastNode->getPosition() + sf::Vector2f(-x, -y));
		m_Nodes.push_back(newNode);

		m_GrowDelta--;
	}

	// FADING TAIL
	sf::Uint32 size = m_Nodes.size();
	float alpha = 255.f / size;
	for (int i = size - 1; i >= 0; i--)
	{
		m_Nodes.at(i)->setFillColor(
			sf::Color(m_Color.r, m_Color.g, m_Color.b, (unsigned short)Utils::clamp(255.f - (int)(alpha * i), 40.f, 255.f))
			);
	}

	m_CanMove = true;
}

void Snake::Render(sf::RenderWindow& window)
{
	for (auto node : m_Nodes)
		window.draw(*node);		
}

void Snake::SetPosition(sf::Vector2f position)
{
	m_Nodes.front()->setPosition(position);
}

void Snake::SetDirection(Direction dir)
{
	m_CanMove = false;

	if (dir == Direction::Up && m_Direction != Direction::Down)
	{
		m_Direction = Direction::Up;
	}
	else if (dir == Direction::Down && m_Direction != Direction::Up)
	{
		m_Direction = Direction::Down;
	}
	else if (dir == Direction::Left && m_Direction != Direction::Right)
	{
		m_Direction = Direction::Left;
	}
	else if (dir == Direction::Right && m_Direction != Direction::Left)
	{
		m_Direction = Direction::Right;
	}
}