#pragma once

#include <SD.h>
#include "hardware/Camera.h"

class CameraWriter {
private:
	Camera& _camera;
	SDClass* _sd;

public:
	CameraWriter(Camera& camera, SDClass* sd);
	void captureAndSaveImage(String filename);
};
