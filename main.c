#include "raylib.h"
#include "variables.c"
#include "util.c"
#include "fantasma.c"

int sin_recolectar = 0;
int startTime = -1;

int main()
{
    int perdiste = 0;
    char puntosString [50];
    sprintf (puntosString, "Puntos: %d", puntos);

    InitWindow(screenWidth, screenHeight, titulo);
    InitAudioDevice();
    Music music = LoadMusicStream("./assets/music.ogg");
    PlayMusicStream(music);
    
    struct Player player = { 1, 5, 0, 0 };

    Texture2D plyTex = LoadTexture("assets/player.png"); 
    plyTex.width = BLOCKSIZE * 5;
    plyTex.height = BLOCKSIZE;
  
    int frameWidth = plyTex.width / 5;
    int frameHeight = plyTex.height;

    Rectangle sourceRec = { 0.0f, 0.0f, (float)frameWidth, (float)frameHeight };
    Rectangle destRec = { 0, 0, (float)frameWidth, (float)frameHeight };
    Vector2 origin = { (float)frameWidth * 0.5, (float)frameHeight * 0.5 };
    Rectangle frameRec = { 0.0f, 0.0f, (float)plyTex.width / 5, (float)plyTex.height };
 
    // Cargando texturas
    
    phantonF = getTexture("assets/phantonF.png");
    phantonF.width = BLOCKSIZE;
    phantonF.height = BLOCKSIZE;

    phantonR = getTexture("assets/phantonR.png");
    phantonR.width = BLOCKSIZE;
    phantonR.height = BLOCKSIZE;

    phantonA = getTexture("assets/phantonA.png");
    phantonA.width = BLOCKSIZE;
    phantonA.height = BLOCKSIZE;

    Texture2D texture = getTexture("assets/wallBrown.png");
    texture.width = BLOCKSIZE;
    texture.height = BLOCKSIZE;
    
    Texture2D joseoTexture = getTexture("assets/joseo.png");
    joseoTexture.width = BLOCKSIZE;
    joseoTexture.height = BLOCKSIZE;
    
    Texture2D coffeTexture = getTexture("assets/coffe.png");
    coffeTexture.width = BLOCKSIZE;
    coffeTexture.height = BLOCKSIZE;
    
    Texture2D character = getTexture("assets/maton.png");
    character.width = BLOCKSIZE;
    character.height = BLOCKSIZE;
    
    Texture2D intecTexture = getTexture("assets/intecMAN.png");
    intecTexture.width *= 0.15;
    intecTexture.height *= 0.15;


    struct Fantasma fantasmas[8] = {
        {10, 10, 0.1, 0, phantonF, 0, 0, 0, 0, 'f'},
        {10, 11, 0.1, 0, phantonR, 0, 0, 0, 0, 'r'},
        {11, 10, 0.1, 0, phantonF, 0, 0, 0, 0, 'f'},
        {11, 11, 0.1, 0, phantonR, 0, 0, 0, 0, 'r'},
        {10, 10, 0.1, 0, phantonF, 0, 0, 0, 0, 'f'},
        {10, 11, 0.1, 0, phantonR, 0, 0, 0, 0, 'r'},
        {11, 10, 0.1, 0, phantonF, 0, 0, 0, 0, 'f'},
        {11, 11, 0.1, 0, phantonR, 0, 0, 0, 0, 'r'}
    };

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        UpdateMusicStream(music);

        if (startTime > 0) {
            startTime -= GetFrameTime();
        }

        if ((startTime > -1) && (startTime <= 0)) {
            for (int i = 0; i < 8; i++) {
                fantasmas[i].letra = 'f';
            }
        }

        sprintf (puntosString, "Puntos: %d", puntos);
        
        
        if (IsKeyDown(KEY_RIGHT)) {
            rotation = 0;
            player.vx = velocidad;
            player.vy = 0;
        }
        if (IsKeyDown(KEY_LEFT)) {
            rotation = 180;
            player.vx = -velocidad;
            player.vy = 0;
        }
        
        if (IsKeyDown(KEY_UP)) {
            rotation = 270;
            player.vy = -velocidad;
            player.vx = 0;
        }
        
        if (IsKeyDown(KEY_DOWN)) {
            rotation = 90;
            player.vy = velocidad;
            player.vx = 0;
        }
        
        
        framesCounter++;
        
        if (framesCounter >= (60/framesSpeed))
        {
            framesCounter = 0;
            currentFrame++;
            
            if (currentFrame > 5) currentFrame = 0;
            
            frameRec.x = (float)currentFrame * (float)plyTex.width / 5;
            sourceRec.x = frameRec.x;
        }
        
        BeginDrawing();
            ClearBackground((Color){ 100, 28, 28 * 2, 255 });
            DrawTexture(intecTexture, 400 - (intecTexture.width / 2), 10, WHITE);     
            
            DrawText(puntosString, 30, marginY, 28, WHITE);
            
            DrawText("Joseo: ", 30, marginY + 50, 28, WHITE);
            DrawTexture(joseoTexture, 130, marginY +50, WHITE);        
            
            DrawTexture(coffeTexture, 130, marginY + 100, WHITE);        
            DrawText("Puntos: ", 30, marginY + 100, 28, WHITE);
        
            DrawTexture(character, 130, marginY + 150, WHITE);        
            DrawText("Maton: ", 30, marginY + 150, 28, WHITE);
            
            DrawRectangle(marginX, marginY, BLOCKSIZE*X, BLOCKSIZE*Y, BLACK);
            DrawRectangleLines(marginX - 1, marginY - 1, BLOCKSIZE*X + 2, BLOCKSIZE*Y + 2, BLACK);
            
            for (int i = 0; i < 8; i++) {
                fantasmas[i] = updateFantasma(fantasmas[i]);
                /*
                if ((abs(round(fantasmas[i].x - player.x)) < 2) && (abs(round(fantasmas[i].y - player.y)) < 2)) {
                    perdiste = 1;
                }
                */
                
                if ((round(fantasmas[i].x) == round(player.x)) && (round(fantasmas[i].y) == round(player.y))) {
                    if (fantasmas[i].letra != 'a') {
                        perdiste = 1;
                    } else {
                        puntos += 2;
                        fantasmas[i].x = 10;
                        fantasmas[i].y = 10;
                        fantasmas[i].letra = 'f';
                    }
                }
                
            }

            sin_recolectar = 0;
           for (int x = 0; x < X; x++) {            
                for (int y = 0; y < Y; y++) {
                    for (int i = 0; i < 8; i++) {
                        fantasmas[i] = updateFantasmaColision(fantasmas[i], x, y);
                    }

                    if (map[x][y] == 1) {
                        DrawTexture(texture, marginX +x * BLOCKSIZE, marginY + y * BLOCKSIZE, WHITE);        
                    }
                    else if (map[x][y] == JOSEO) {
                        DrawTexture(joseoTexture, marginX +x * BLOCKSIZE, marginY + y * BLOCKSIZE, WHITE);        
                    }
                    else if (map[x][y] == COFFE) {
                        DrawTexture(coffeTexture, marginX +x * BLOCKSIZE, marginY + y * BLOCKSIZE, WHITE);        
                        sin_recolectar++;
                    }
                    /*
                    else if (map[x][y] == F) {
                        DrawTexture(phantonF, marginX +x * BLOCKSIZE, marginY + y * BLOCKSIZE, WHITE);        
                    }
                    else if (map[x][y] == R) {
                        DrawTexture(phantonR, marginX +x * BLOCKSIZE, marginY + y * BLOCKSIZE, WHITE);        
                    }
                    else if (map[x][y] == PJ) {
                        DrawTexture(character, marginX +x * BLOCKSIZE, marginY + y * BLOCKSIZE, WHITE);        
                    }
                    */

                    // Colision                
                    if ((round(player.x) == x) && (round(player.y) == y)) {
                        
                        destRec.x = marginX + player.x * BLOCKSIZE + BLOCKSIZE / 2;
                        destRec.y = marginY + player.y * BLOCKSIZE + BLOCKSIZE / 2;
                        
                        // DrawTextureRec(plyTex, frameRec, (Vector2){marginX + player.x * BLOCKSIZE, marginY + player.y * BLOCKSIZE}, WHITE);
                        DrawTexturePro(plyTex, sourceRec, destRec, origin, (float)rotation, WHITE);
                    
                        if (map[x][y] == 3) {
                            map[x][y] = 0;
                            puntos += 1;
                        }

                        if (map[x][y] == 2) {
                            map[x][y] = 0;
                            for (int i = 0; i < 8; i++) {
                                fantasmas[i].letra = 'a';
                                startTime = 300;
                            }
                        }

                        if (map[(int) round(player.x - 0.5) + 1][y] == 1) {
                            player.x -= 0.1;
                            player.vx = 0;                            
                        }
                        
                        if (map[(int) round(player.x + 0.5) - 1][y] == 1) {
                            player.x += 0.1;
                            player.vx = 0;                            
                        }
                        
                        if (map[x][(int) round(player.y - 0.5) + 1] == 1) {
                            player.y -= 0.1;
                            player.vy = 0;                            
                        }
                        
                        if (map[x][(int) round(player.y + 0.5) - 1] == 1) {
                            player.y += 0.1;
                            player.vy = 0;                            
                        }
                    
                        player.x += player.vx;
                        player.y += player.vy;                        
                    }
                }
            }

            if (sin_recolectar == 0) {
                DrawRectangle(0, 0, screenWidth, screenHeight, BLACK);
                DrawText("Ganaste!", (screenWidth - MeasureText("Ganaste!", 100)) / 2, 300, 100, WHITE);   
            }
            
            if (perdiste){
                DrawRectangle(0, 0, screenWidth, screenHeight, BLACK);
                DrawText("Perdiste!", (screenWidth - MeasureText("Perdiste!", 100)) / 2, 300, 100, WHITE);   
            }

        EndDrawing();

    }

    CloseWindow();        
    
    return 0;
}