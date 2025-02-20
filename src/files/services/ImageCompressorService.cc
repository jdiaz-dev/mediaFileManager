#include <ImageCompressorService.h>
#include <vips/vips8>

using namespace std;
using namespace vips;

void ImageCompressorService::compress(const string& inputPath, const string& outputPath, int quality){
     if (VIPS_INIT("compress_image"))
        vips_error_exit("Failed to initialize VIPS");

    // Load the image
    VImage img = VImage::new_from_file(inputPath.c_str());

    // Compress and save based on file extension
    if (outputPath.find(".jpg") != std::string::npos || outputPath.find(".jpeg") != std::string::npos) {
        img.jpegsave(outputPath.c_str(), VImage::option()->set("Q", quality));
    } else if (outputPath.find(".png") != std::string::npos) {
        img.pngsave(outputPath.c_str(), VImage::option()->set("compression", 9));
    } else if (outputPath.find(".webp") != std::string::npos) {
        img.webpsave(outputPath.c_str(), VImage::option()->set("Q", quality));
    } else {
        vips_error_exit("Unsupported format!");
    }

    vips_shutdown();
}

/* int main() {
    compressImage("input.jpg", "output.jpg", 75);  // Compress to 75% quality
    compressImage("input.png", "output.png", 9);   // Max PNG compression
    compressImage("input.webp", "output.webp", 80); // WebP compression
    return 0;
}
 */