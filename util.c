
struct Player {
    float x;
    float y;
    float vx;
    float vy;
};

Texture2D getTexture(char* src) {
    Image image = LoadImage(src);
    Texture2D texture = LoadTextureFromImage(image);
    UnloadImage(image);
    return texture;
}

