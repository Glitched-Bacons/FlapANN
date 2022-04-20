#pragma once

#include <deque>
#include <memory>
#include "Pipe.h"

class PipesGenerator : public NodeScene
{
	/**
	 * \brief Contains data needed to calculate randomized offsets
	 */
	struct PipeOffset
	{
		int minPipeOffset{0};
		int maxPipeOffset{0};
	};

public:
	/**
	 * \brief The main constructor of the pipe generator.
	 * \param textures Texture manager holds all the available textures in the game.
	 * \param clippingPoints pipe clipping points (beginning and end of window).
	 */
	explicit PipesGenerator(const TextureManager& textures, const sf::Vector2i& screenSize);

	/**
	 * \brief Updates the logic of the pipe. Including positions on the screen or
	 *		  the deletion or generation of the pipe.
	 * \param deltaTime the time that has passed since the game was last updated
	 *
	 * Works analogues to the drawThis(), updates all things related to itself
	 */
	void updateThis(const sf::Time& deltaTime) override;

	/**
	 * \brief Draws the pipe to the passed target.
	 * \param target where it should be drawn to
	 * \param states provides information about rendering process (transform, shader, blend mode)
	 */
	void drawThis(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	/**
	 * \brief Calculates random pipe offset using random number generator. 
	 * \return x and y offset values.
	 */
	[[nodiscard]] inline sf::Vector2f calculateRndPipeOffset() const;

	/**
	 * \brief Retrieves the position of the last pipe added to the deque.
	 * \return Position (x, y) of the pipe.
	 */
	[[nodiscard]] inline float getLastPipeXPosition() const;

	/**
	 * \brief It generates both bottom and upper pipe.
	 */
	void generatePipe();

	/**
	 * \brief Deletes pipes outside of the window frame.
	 */
	void deletePipes();

	/**
	 * \brief Updates pipes' position on the screen.
	 * \param deltaTime the time that has passed since the game was last updated
	 */
	void updatePipesPosition(const sf::Time& deltaTime) const;

	/**
	 * \brief Creates bottom pipe. It also prepares its properties,
	 *		  such as position or origin.
	 * \param offset Randomized offset of the pipe.
	 * \param prevPipeOffset Previous pipe offset.
	 * \return A pointer to newly created pipe.
	 */
	std::unique_ptr<Pipe> createBottomPipe(const sf::Vector2f& offset, const float& prevPipeXPos) const;

	/**
	 * \brief Creates bottom pipe. It also prepares its properties,
	 *		  such as position or origin.
	 * \param offset Randomized offset of the pipe.
	 * \param prevPipeOffset Previous pipe offset.
	 * \return A pointer to newly created pipe.
	 */
	std::unique_ptr<Pipe> createUpperPipe(const sf::Vector2f& offset, const float& prevPipeXPos) const;

	/**
	 * \brief Determines if the pipe is outside the window area.
	 * \return True if the bird is out of sight. False otherwise.
	 */
	bool isPipeOutOfSight() const;

	/**
	 * \brief Determines whether a pipe should be generated at a given time.
	 * \return Tru if the pipe is in window frame. False otherwise.
	 */
	bool isLastPipeInsideWindowFrame() const;

private:
	const TextureManager& mTextures;

	PipeOffset xCoordinate{60, 100};
	PipeOffset yCoordinate{30,};

	/** Used to determine pipe clipping point */
	int mClippingPoint;

	/**	Distance between bottom and top pipe */
	const float& offsetBetweenPipes{40};

	/** Produces high quality unsigned integer random numbers */
	static std::mt19937 engine;

	/** Random number generator, used in order to seed engine */
	static std::random_device rndDevice;

	/** Hold pipes that are currently being rendered on the screen */
	std::deque<std::unique_ptr<Pipe>> mPipes;
};