#include <unordered_set>
#include <string> 
#include <vector> 
#include <memory>
#include "ImageCompressorService.h"

using namespace std;

class MediaFilesManagerService {
    private:
        shared_ptr<ImageCompressorService> compressorService;
    public:
        MediaFilesManagerService(const shared_ptr<ImageCompressorService>& service);
        void compressFiles(vector<string> filePaths);
};
