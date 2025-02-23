#pragma once
using namespace std;

class ImageCompressorService {
    public:
        ImageCompressorService();
        void compress(const string& inputPath, const string& outputPath, int quality);
};
