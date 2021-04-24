#include "Block.h"

Block* Block::blocks[256];

Block::Block(int texture, unsigned int id) : id(id), 
	texture{texture ,texture ,texture ,texture ,texture ,texture}{

}