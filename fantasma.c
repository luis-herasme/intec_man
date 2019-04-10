
struct Fantasma {
    float x;
    float y;
    float vx;
    float vy;
    Texture2D textura;
    int think_1;
	int think_2;
	int think_3;
	int think_4;
	char letra;
};

struct Fantasma updateFantasma(struct Fantasma fantasma) {

	if (fantasma.letra == 'f') {
		fantasma.textura = phantonF;
	}

	if (fantasma.letra == 'r') {
		fantasma.textura = phantonR;
	}

	if (fantasma.letra == 'a') {
		fantasma.textura = phantonA;
	}
	
	DrawTexture(fantasma.textura, marginX + fantasma.x * BLOCKSIZE, marginY + fantasma.y * BLOCKSIZE, WHITE);
    fantasma.x += fantasma.vx;
    fantasma.y += fantasma.vy;     
    return fantasma;
}


struct Fantasma updateFantasmaColision(struct Fantasma fantasma, int x, int y) {


    // Colision

	if ((round(fantasma.x) == x) && (round(fantasma.y) == y)) {
	    
	    if (map[(int) round(fantasma.x - 0.5) + 1][y] == 1) {
	        fantasma.x -= 0.1;
	        fantasma.vx = 0;                
	    }
	    
	    if (map[(int) round(fantasma.x + 0.5) - 1][y] == 1) {
	        fantasma.x += 0.1;
	        fantasma.vx = 0;                            
	    }
	    
	    if (map[x][(int) round(fantasma.y - 0.5) + 1] == 1) {
	        fantasma.y -= 0.1;
	        fantasma.vy = 0;
	    }
	    
	    if (map[x][(int) round(fantasma.y + 0.5) - 1] == 1) {
	        fantasma.y += 0.1;
	        fantasma.vy = 0;
	    }



	    // AI
		if (rand() % 20 == 2) {
			
			int probabilidad = rand() % 4 + 1;

			fantasma.think_1 = 0;
			fantasma.think_2 = 0;
			fantasma.think_3 = 0;
			fantasma.think_4 = 0;

			if (probabilidad == 1) fantasma.think_1 = 1;
			if (probabilidad == 2) fantasma.think_2 = 1;
			if (probabilidad == 3) fantasma.think_3 = 1;
			if (probabilidad == 4) fantasma.think_4 = 1;
		}
		

		if (fantasma.think_1) fantasma.vx = 0.1;
		if (fantasma.think_2) fantasma.vx = -0.1;
		if (fantasma.think_3) fantasma.vy = 0.1;
		if (fantasma.think_4) fantasma.vy = -0.1;
	}

	return fantasma;
}
