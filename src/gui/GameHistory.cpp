#include <iostream>
#include <list>

#include <gui/GameHistory.hpp>
#include <gui/GameBoard.hpp>
#include <engine/board/Board.hpp>
#include <engine/board/Move.hpp>
#include <engine/pieces/Piece.hpp>
#include <engine/player/Player.hpp>
#include <engine/Alliance.hpp>

/* HistoryRow */

HistoryRow::HistoryRow(sf::Font &font)
{
	whiteMove.setFont(font);
	whiteMove.setCharacterSize(18);
	whiteMove.setFillColor(sf::Color::Black);

	blackMove.setFont(font);
	blackMove.setCharacterSize(18);
	blackMove.setFillColor(sf::Color::Black);

	bottomDividerRect.setSize(sf::Vector2f(160, 2));
	bottomDividerRect.setFillColor(sf::Color(0, 0, 0, 100));
}

void HistoryRow::setPosition(sf::Vector2f position)
{
	whiteMove.setPosition(position + sf::Vector2f(7, 0));
	blackMove.setPosition(position + sf::Vector2f(80, 0) + sf::Vector2f(7, 0));
	bottomDividerRect.setPosition(position + sf::Vector2f(0, 23));
}

void HistoryRow::setWhiteMove(std::string move)
{
	whiteMove.setString(move);
}

void HistoryRow::setBlackMove(std::string move)
{
	blackMove.setString(move);
}

sf::Vector2f HistoryRow::getPosition() const
{
	return bottomDividerRect.getPosition() + sf::Vector2f(0, 2);
}

std::string HistoryRow::getWhiteMove()
{
	return whiteMove.getString();
}

std::string HistoryRow::getBlackMove()
{
	return blackMove.getString();
}

void HistoryRow::draw(sf::RenderWindow &window)
{
	window.draw(whiteMove);
	window.draw(blackMove);
	window.draw(bottomDividerRect);
}

/* GameHistoryBlock */

GameHistoryBlock::GameHistoryBlock()
{
	if (!font.loadFromFile(std::string(PROJECT_SOURCE_DIR) + "/resources/fonts/arial.ttf"))
		throw std::runtime_error("Failed to load font!");

	scrollPercentageTop = 0.f;
	scrollPercentageBottom = 100.f;

	scrollBarClicked = false;

	gameHistoryAreaRect.setSize(sf::Vector2f(180, 560));
	gameHistoryAreaRect.setPosition(780, 75);
	gameHistoryAreaRect.setFillColor(sf::Color(253, 245, 230));

	scrollBarRect.setSize(sf::Vector2f(20, 560));
	scrollBarRect.setPosition(940, 75);
	scrollBarRect.setFillColor(sf::Color(200, 200, 200));

	dividerRect.setSize(sf::Vector2f(2, 0));
	dividerRect.setPosition(860, 75);
	dividerRect.setFillColor(sf::Color(0, 0, 0, 100));

	scale = sf::Vector2f(1, 1);
	mouseOffset = sf::Vector2f(0, 0);

	playerNames[0].setFont(font);
	playerNames[0].setCharacterSize(18);
	playerNames[0].setFillColor(sf::Color::Black);
	playerNames[0].setString("White");
	playerNames[0].setPosition(800, 50);

	playerNames[1].setFont(font);
	playerNames[1].setCharacterSize(18);
	playerNames[1].setFillColor(sf::Color::Black);
	playerNames[1].setString("Black");
	playerNames[1].setPosition(880, 50);

	view.setSize(160, 560);
	view.setCenter(860, 355);
	view.setViewport(sf::FloatRect(0.8125f, 0.107f, 0.1667f, 0.8f));
}

sf::View GameHistoryBlock::getView() const
{
	return view;
}

void GameHistoryBlock::redo(Board *board, MoveLog &moveLog)
{
	std::list<std::string> pastChecks;
	for (long unsigned int i = 0; i < historyRows.size(); i++)
	{
		if (historyRows[i].getWhiteMove().find("+") != std::string::npos)
			pastChecks.push_back(std::to_string(i) + 'W');
		if (historyRows[i].getBlackMove().find("+") != std::string::npos)
			pastChecks.push_back(std::to_string(i) + 'B');
	}
	historyRows.clear();
	int currentRow = 0;
	if (moveLog.getMoves().size() > 0)
	{
		for (long unsigned int i = 0; i < moveLog.getMoves().size(); i += 2)
		{
			HistoryRow historyRow(font);
			historyRow.setPosition(sf::Vector2f(gameHistoryAreaRect.getPosition().x, 75 + currentRow * 25));
			historyRow.setWhiteMove(
				moveLog.getMoves()[i]->stringify() +
				((pastChecks.front() == std::to_string(currentRow) + 'W') ? pastChecks.pop_front(), "+"
																		  : ""));
			if (i + 1 < moveLog.getMoves().size())
			{
				historyRow.setBlackMove(
					moveLog.getMoves()[i + 1]->stringify() +
					((pastChecks.front() == std::to_string(currentRow) + 'B') ? pastChecks.pop_front(), "+"
																			  : ""));
			}
			historyRows.push_back(historyRow);
			currentRow++;
		}
		auto lastMove = moveLog.getMoves().back();
		const std::string lastMoveString = lastMove->stringify() + calculateCheckAndCheckMate(board);
		HistoryRow &lastRow = historyRows.back();
		if (AllianceUtils::isWhite(lastMove->getMovedPiece()->getPieceAlliance()))
			lastRow.setWhiteMove(lastMoveString);
		else
			lastRow.setBlackMove(lastMoveString);
	}
	dividerRect.setSize(sf::Vector2f(2, 25 * currentRow));
	gameHistoryAreaRect.setSize(sf::Vector2f(180, std::max(25 * currentRow, 560)));
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
	sf::FloatRect viewPortDim = view.getViewport();
	sf::FloatRect dim(windowSize.x * viewPortDim.left, windowSize.y * viewPortDim.top, windowSize.x * viewPortDim.width, windowSize.y * viewPortDim.height);
	if (dim.contains(event.x, event.y))
	{
		if (event.delta > 0)
		{
			if (scrollPercentageTop > 0)
				view.move(0, -25);
		}
		else if (scrollPercentageBottom < 100)
			view.move(0, 25);
	}
	updateScrollPercentage(windowSize);
}
void GameHistoryBlock::scrollBarScrolled(sf::Event::MouseButtonEvent &event, bool buttonClickedOrReleased)
{
	if (buttonClickedOrReleased && event.button == sf::Mouse::Button::Left && scrollBarRect.getGlobalBounds().contains(event.x, event.y))
	{
		scrollBarClicked = true;
		mouseOffset = scrollBarRect.getPosition() - sf::Vector2f(event.x, event.y);
	}
	else
		scrollBarClicked = false;
}

void GameHistoryBlock::scroll(sf::RenderWindow &window)
{
	if (scrollBarClicked)
	{
		sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window)),
					 currentRectPosition = scrollBarRect.getPosition(),
					 newRectPosition = sf::Vector2f(currentRectPosition.x, mousePosition.y + mouseOffset.y),
					 distance = newRectPosition - currentRectPosition,
					 windowSize = window.getView().getSize();
		int numberOfEntriesTraversed = distance.y / 25;
		if (distance.y > 0 && scrollPercentageBottom < 100.f)
		{
			view.move(0, 25 * numberOfEntriesTraversed);
		}
		else if (distance.y < 0 && scrollPercentageTop > 0.f)
		{
			view.move(0, 25 * numberOfEntriesTraversed);
		}
		updateScrollPercentage(windowSize);
	}
}

void GameHistoryBlock::update(sf::RenderWindow &window)
{
	sf::Vector2u windowSize = window.getSize();
	playerNames[0].setPosition(windowSize.x - 160, 50);
	playerNames[1].setPosition(windowSize.x - 80, 50);
	gameHistoryAreaRect.setPosition(windowSize.x - 180, 75);
	scrollBarRect.setPosition(windowSize.x - 20, scrollBarRect.getPosition().y);
	dividerRect.setPosition(windowSize.x - 100, 75);
	float y = view.getSize().y;
	view.setSize(160, std::min(560u, windowSize.y - 75));
	y -= view.getSize().y;
	view.setCenter(windowSize.x - 100, view.getCenter().y - y / 2);
	view.setViewport(sf::FloatRect((windowSize.x - 180) / static_cast<float>(windowSize.x), 75 / static_cast<float>(windowSize.y), 160 / static_cast<float>(windowSize.x), (std::min(560u, windowSize.y - 75)) / static_cast<float>(windowSize.y)));
	updateScrollPercentage(sf::Vector2f(windowSize.x, windowSize.y));
	for (auto &historyRow : historyRows)
		historyRow.setPosition(sf::Vector2f(gameHistoryAreaRect.getPosition().x, historyRow.getPosition().y - 25));
}

void GameHistoryBlock::updateScrollPercentage(sf::Vector2f windowSize)
{
	if (historyRows.size() == 0 || (historyRows.front().getPosition().y > view.getCenter().y - view.getSize().y / 2 &&
									historyRows.back().getPosition().y < view.getCenter().y + view.getSize().y / 2))
	{
		scrollPercentageTop = 0.f;
		scrollPercentageBottom = 100.f;
		scrollBarRect.setSize(sf::Vector2f(20, view.getSize().y));
		scrollBarRect.setPosition(windowSize.x - 20, 75);
	}
	else
	{
		scrollPercentageBottom = (view.getCenter().y - 75 + view.getSize().y / 2) / (historyRows.back().getPosition().y - 75) * 100.f;
		scrollPercentageTop = std::max(0.f, scrollPercentageBottom - 100.f * view.getSize().y / (historyRows.back().getPosition().y - 75));
		scrollBarRect.setSize(sf::Vector2f(20, std::min(560.f, windowSize.y - 75.f) * view.getSize().y / (historyRows.back().getPosition().y - 75)));
		scrollBarRect.setPosition(windowSize.x - 20, 75 + view.getSize().y * scrollPercentageTop / 100.f);
	}
}

void GameHistoryBlock::draw(sf::RenderWindow &window)
{
	update(window);
	window.draw(playerNames[0]);
	window.draw(playerNames[1]);
	window.draw(scrollBarRect);
	window.setView(view);
	window.draw(gameHistoryAreaRect);
	window.draw(dividerRect);
	for (auto &historyRow : historyRows)
		historyRow.draw(window);
}