#include <filesystem> 
#include <vips/vips8>
#include "ImageCompressorService.h"
#include <iostream>

using namespace std;
using namespace vips;

ImageCompressorService::ImageCompressorService(){}
void ImageCompressorService::compress(const std::string& inputPath, const std::string& outputPath, int quality) {
    if (VIPS_INIT("compress_image")) {
        throw invalid_argument("Failed to initialize VIPS");
    }
    try {
        filesystem::path outputDir = filesystem::path(outputPath).parent_path();
        if (!filesystem::exists(outputDir)) {
            filesystem::create_directories(outputDir);  // ✅ Create directory if missing
        }
        VImage img = VImage::new_from_file(inputPath.c_str());
        if (outputPath.rfind(".jpg") != string::npos || outputPath.rfind(".jpeg") != string::npos) {
            img.jpegsave(outputPath.c_str(), VImage::option()->set("Q", quality));
        } else if (outputPath.rfind(".png") != string::npos) {
            img.pngsave(outputPath.c_str(), VImage::option()->set("compression", 9));
        } else if (outputPath.rfind(".webp") != string::npos) {
            img.webpsave(outputPath.c_str(), VImage::option()->set("Q", quality));
        } else {
            vips_error_exit("Unsupported format!");
        }
        vips_shutdown();
    } catch (const std::exception& e) {
        throw invalid_argument("Failed to compress image");
    }
}

