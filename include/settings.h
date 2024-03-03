#pragma once

const unsigned int WINDOW_WIDTH = 840;
const unsigned int WINDOW_HEIGHT = 520;

const float TILE_SIZE = 64;
const std::vector<std::string> map { // 20x20
	"XXXXXXXXXXXXXXXXXXXX",
	"X                  X",
	"X                  X",
	"X  X     XXXXX     X",
	"X  X         X     X",
	"X  X         X     X",
	"X  X         X     X",
	"X  X    P    X     X",
	"X  X         X     X",
	"X  X         X     X",
	"X  X         X     X",
	"X  X         XXX   X",
	"X      X           X",
	"X     XXXXX        X",
	"X        X         X",
	"X        X         X",
	"X                  X",
	"X                  X",
	"X                  X",
	"XXXXXXXXXXXXXXXXXXXX"
};

const unsigned int cameraXAxis = 80;
const unsigned int cameraYAxis = 40;