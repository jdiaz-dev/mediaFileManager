#include <unordered_set>
#include <string> 
#include <vector> 
#include <memory>
#include <ImageCompressorService.h>

using namespace std;

class MediaFilesManagerService {
    private:
        static const unordered_set<string> txtFormats = {".pdf"};
        static const unordered_set<string> imageFormats = {".jpg", ".png", ".gif", ".bmp", ".jpeg"};

        void compressFiles(string vector<files>){
            if(jpg){

            }
        }
        void saveFiles(){

        }
    public:
        MediaFilesManagerService(shared_ptr<ImageCompressorService> ics, string entity, vector<string> files);
        void help(){
            this->compressFiles();
            // this->saveFiles(); 
        }


};