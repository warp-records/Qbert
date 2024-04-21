

	EdgeCubies();
EdgeCubies(uint16_t top, uint16_t bottom, 
		uint16_t left, uint16_t right,
		uint8_t front, uint8_t back);
    
EdgeCubies(Cube const& largeCube);

//Normalized so top left front cube is never moved
EdgeCubies rotHoriz(Row line, Direction dir) const;
EdgeCubies rotXAxis(Column line, Direction dir) const;

EdgeCubies& operator=(const EdgeCubies& other) = default;

std::array<EdgeCubies, 4> getNeighbors() const;