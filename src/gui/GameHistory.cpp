#include <iostream>

#include "../../include/gui/GameHistory.hpp"
#include "../../include/gui/GameBoard.hpp"
#include "../../include/engine/board/Board.hpp"
#include "../../include/engine/board/Move.hpp"
#include "../../include/engine/pieces/Piece.hpp"
#include "../../include/engine/player/Player.hpp"
#include "../../include/engine/Alliance.hpp"

/* HistoryRow */

HistoryRow::HistoryRow(sf::Font &font)
{
	this->whiteMove.setFont(font);
	this->whiteMove.setCharacterSize(18);
	this->whiteMove.setFillColor(sf::Color::Black);

	this->blackMove.setFont(font);
	this->blackMove.setCharacterSize(18);
	this->blackMove.setFillColor(sf::Color::Black);

	this->bottomDividerRect.setSize(sf::Vector2f(160, 2));
	this->bottomDividerRect.setFillColor(sf::Color(0, 0, 0, 100));
}

void HistoryRow::setPosition(sf::Vector2f position)
{
	this->whiteMove.setPosition(position);
	this->blackMove.setPosition(position + sf::Vector2f(80, 0));
	this->bottomDividerRect.setPosition(position + sf::Vector2f(-10, 22));
}

void HistoryRow::setWhiteMove(std::string move)
{
	this->whiteMove.setString(move);
}

void HistoryRow::setBlackMove(std::string move)
{
	this->blackMove.setString(move);
}

sf::Vector2f HistoryRow::getPosition() const
{
	return this->bottomDividerRect.getPosition() + sf::Vector2f(0, 2);
}

std::string HistoryRow::getWhiteMove()
{
	return this->whiteMove.getString();
}

std::string HistoryRow::getBlackMove()
{
	return this->blackMove.getString();
}

void HistoryRow::draw(sf::RenderWindow &window)
{
	window.draw(this->whiteMove);
	window.draw(this->blackMove);
	window.draw(this->bottomDividerRect);
}

/* GameHistoryBlock */

GameHistoryBlock::GameHistoryBlock()
{
	if (!this->font.loadFromFile("../resources/fonts/arial.ttf"))
	{
		std::cerr << "Error loading font" << std::endl;
		exit(EXIT_FAILURE);
	}

	this->scrollPercentageTop = 0.f;
	this->scrollPercentageBottom = 100.f;

	this->scrollBarClicked = false;

	this->gameHistoryAreaRect.setSize(sf::Vector2f(180, 560));
	this->gameHistoryAreaRect.setPosition(780, 75);
	this->gameHistoryAreaRect.setFillColor(sf::Color(253, 245, 230));

	this->scrollBarRect.setSize(sf::Vector2f(20, 560));
	this->scrollBarRect.setPosition(940, 75);
	this->scrollBarRect.setFillColor(sf::Color(200, 200, 200));

	this->dividerRect.setSize(sf::Vector2f(2, 0));
	this->dividerRect.setPosition(860, 75);
	this->dividerRect.setFillColor(sf::Color(0, 0, 0, 100));

	this->scale = sf::Vector2f(1, 1);
	this->mouseOffset = sf::Vector2f(0, 0);

	this->playerNames[0].setFont(this->font);
	this->playerNames[0].setCharacterSize(18);
	this->playerNames[0].setFillColor(sf::Color::Black);
	this->playerNames[0].setString("White");
	this->playerNames[0].setPosition(800, 50);

	this->playerNames[1].setFont(this->font);
	this->playerNames[1].setCharacterSize(18);
	this->playerNames[1].setFillColor(sf::Color::Black);
	this->playerNames[1].setString("Black");
	this->playerNames[1].setPosition(880, 50);

	view.setSize(160, 560);
	view.setCenter(860, 355);
	view.setViewport(sf::FloatRect(0.8125f, 0.107f, 0.1667f, 0.8f));
}

sf::View GameHistoryBlock::getView() const
{
	return this->view;
}

void GameHistoryBlock::redo(Board *board, MoveLog &moveLog)
{
	this->historyRows.clear();
	int currentRow = 0;
	if (moveLog.getMoves().size() > 0)
	{
		for (long unsigned int i = 0; i < moveLog.getMoves().size(); i += 2)
		{
			HistoryRow historyRow(this->font);
			historyRow.setPosition(sf::Vector2f(this->gameHistoryAreaRect.getPosition().x, 75 + currentRow * 25));
			historyRow.setWhiteMove(moveLog.getMoves()[i]->stringify());
			if (i + 1 < moveLog.getMoves().size())
			{
				historyRow.setBlackMove(moveLog.getMoves()[i + 1]->stringify());
			}
			this->historyRows.push_back(historyRow);
			currentRow++;
		}
		const auto lastMove = moveLog.getMoves().back();
		const std::string lastMoveString = lastMove->stringify() + calculateCheckAndCheckMate(board);
		auto lastRow = this->historyRows.back();
		if (AllianceUtils::isWhite(lastMove->getMovedPiece()->getPieceAlliance()))
			lastRow.setWhiteMove(lastMoveString);
		else
			lastRow.setBlackMove(lastMoveString);
	}
	this->dividerRect.setSize(sf::Vector2f(2, 25 * currentRow));
	this->gameHistoryAreaRect.setSize(sf::Vector2f(180, std::max(25 * currentRow, 560)));
}

std::string GameHistoryBlock::calculateCheckAndCheckMate(Board *board)
{
	if (board->getCurrentPlayer()->isInCheckMate())
	{
		return "#";
	}
	else if (board->getCurrentPlayer()->isInCheck())
	{
		return "+";
	}
	return "";
}

void GameHistoryBlock::mouseWheelScrolled(sf::Event::MouseWheelScrollEvent &event, sf::Vector2f windowSize)
{
	sf::FloatRect viewPortDim = this->view.getViewport();
	sf::FloatRect dim(windowSize.x * viewPortDim.left, windowSize.y * viewPortDim.top, windowSize.x * viewPortDim.width, windowSize.y * viewPortDim.height);
	if (dim.contains(event.x, event.y))
	{
		if (event.delta > 0)
		{
			if (this->scrollPercentageTop > 0)
				this->view.move(0, -25);
		}
		else if (this->scrollPercentageBottom < 100)
			this->view.move(0, 25);
	}
	this->updateScrollPercentage(windowSize);
}
void GameHistoryBlock::scrollBarScrolled(sf::Event::MouseButtonEvent &event, bool buttonClickedOrReleased)
{
	if (buttonClickedOrReleased && event.button == sf::Mouse::Button::Left && this->scrollBarRect.getGlobalBounds().contains(event.x, event.y))
	{
		this->scrollBarClicked = true;
		this->mouseOffset = this->scrollBarRect.getPosition() - sf::Vector2f(event.x, event.y);
	}
	else
		this->scrollBarClicked = false;
}

void GameHistoryBlock::scroll(sf::RenderWindow &window)
{
	if (this->scrollBarClicked)
	{
		sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window)),
					 currentRectPosition = this->scrollBarRect.getPosition(),
					 newRectPosition = sf::Vector2f(currentRectPosition.x, mousePosition.y + mouseOffset.y),
					 distance = newRectPosition - currentRectPosition,
					 windowSize = window.getView().getSize();
		int numberOfEntriesTraversed = distance.y / 25;
		if (distance.y > 0 && this->scrollPercentageBottom < 100.f)
		{
			this->view.move(0, 25 * numberOfEntriesTraversed);
		}
		else if (distance.y < 0 && this->scrollPercentageTop > 0.f)
		{
			this->view.move(0, 25 * numberOfEntriesTraversed);
		}
		this->updateScrollPercentage(windowSize);
	}
}

void GameHistoryBlock::update(sf::RenderWindow &window)
{
	sf::Vector2u windowSize = window.getSize();
	this->playerNames[0].setPosition(windowSize.x - 160, 50);
	this->playerNames[1].setPosition(windowSize.x - 80, 50);
	this->gameHistoryAreaRect.setPosition(windowSize.x - 180, 75);
	this->scrollBarRect.setPosition(windowSize.x - 20, this->scrollBarRect.getPosition().y);
	this->dividerRect.setPosition(windowSize.x - 100, 75);
	this->view.setSize(160, std::min(560u, windowSize.y - 75));
	this->view.setCenter(windowSize.x - 100, this->view.getCenter().y);
	this->view.setViewport(sf::FloatRect((windowSize.x - 180) / static_cast<float>(windowSize.x), 75 / static_cast<float>(windowSize.y), 160 / static_cast<float>(windowSize.x), (std::min(560u, windowSize.y - 75)) / static_cast<float>(windowSize.y)));
	this->updateScrollPercentage(sf::Vector2f(windowSize.x, windowSize.y));
}

void GameHistoryBlock::updateScrollPercentage(sf::Vector2f windowSize)
{
	if (this->historyRows.size() == 0 || (this->historyRows.front().getPosition().y > this->view.getCenter().y - this->view.getSize().y / 2 &&
										  this->historyRows.back().getPosition().y < this->view.getCenter().y + this->view.getSize().y / 2))
	{
		this->scrollPercentageTop = 0.f;
		this->scrollPercentageBottom = 100.f;
		this->scrollBarRect.setSize(sf::Vector2f(20, this->view.getSize().y));
		this->scrollBarRect.setPosition(windowSize.x - 20, 75);
	}
	else
	{
		this->scrollPercentageBottom = (this->view.getCenter().y - 75 + this->view.getSize().y / 2) / (this->historyRows.back().getPosition().y - 75) * 100.f;
		this->scrollPercentageTop = std::max(0.f, this->scrollPercentageBottom - 100.f * this->view.getSize().y / (this->historyRows.back().getPosition().y - 75));
		this->scrollBarRect.setSize(sf::Vector2f(20, std::min(560.f, windowSize.y - 75.f) * this->view.getSize().y / (this->historyRows.back().getPosition().y - 75)));
		this->scrollBarRect.setPosition(windowSize.x - 20, 75 + this->view.getSize().y * this->scrollPercentageTop / 100.f);
	}
}

void GameHistoryBlock::draw(sf::RenderWindow &window)
{
	this->update(window);
	window.draw(this->playerNames[0]);
	window.draw(this->playerNames[1]);
	window.draw(this->scrollBarRect);
	window.setView(this->view);
	window.draw(this->gameHistoryAreaRect);
	window.draw(this->dividerRect);
	for (auto &historyRow : this->historyRows)
		historyRow.draw(window);
}