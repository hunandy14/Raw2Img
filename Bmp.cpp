#include "Bmp.hpp"
#include <fstream>

using namespace std;

void RawToBmp(string filename, std::vector<BYTE> &data, int width, int height)
{
	filename += ".bmp";
	fstream bmp;
	bmp.open(filename, ios::binary | ios::out);
	if(!bmp) {
		cout << "unable to build image from bmp" << endl;
		exit(1);
	}
	else {
		int storeW = (width * 3 + 3);
		storeW /= 4;
		storeW *= 4;

		int offset = storeW - width * 3;

		FILE_HEADER file_h;
		file_h.type = 0x424D;
		file_h.size = (DWORD)(14 + sizeof(INFO_HEADER) + storeW * height);
		file_h.reserved1 = 0x0000;
		file_h.reserved2 = 0x0000;
		file_h.offset = (DWORD)(14 + sizeof(INFO_HEADER));

		bmp << (BYTE)(file_h.type >> 8);
		bmp << (BYTE)(file_h.type);
		bmp << (BYTE)(file_h.size);
		bmp << (BYTE)(file_h.size >> 8);
		bmp << (BYTE)(file_h.size >> 16);
		bmp << (BYTE)(file_h.size >> 24);
		bmp << (BYTE)(file_h.reserved1);
		bmp << (BYTE)(file_h.reserved1 >> 8);
		bmp << (BYTE)(file_h.reserved2);
		bmp << (BYTE)(file_h.reserved2 >> 8);
		bmp << (BYTE)(file_h.offset);
		bmp << (BYTE)(file_h.offset >> 8);
		bmp << (BYTE)(file_h.offset >> 16);
		bmp << (BYTE)(file_h.offset >> 24);

		INFO_HEADER info_h;
		info_h.size = sizeof(INFO_HEADER);
		info_h.width = width;
		info_h.height = height;
		info_h.planes = (WORD)1;
		info_h.bits = (WORD)24;
		info_h.compression = 0;
		info_h.imagesize = storeW * height;
		info_h.xresolution = 0;
		info_h.yresolution = 0;
		info_h.ncolours = 0;
		info_h.importantcolours = 0;

		bmp << (BYTE)(info_h.size);
		bmp << (BYTE)(info_h.size >> 8);
		bmp << (BYTE)(info_h.size >> 16);
		bmp << (BYTE)(info_h.size >> 24);
		bmp << (BYTE)(info_h.width);
		bmp << (BYTE)(info_h.width >> 8);
		bmp << (BYTE)(info_h.width >> 16);
		bmp << (BYTE)(info_h.width >> 24);
		bmp << (BYTE)(info_h.height);
		bmp << (BYTE)(info_h.height >> 8);
		bmp << (BYTE)(info_h.height >> 16);
		bmp << (BYTE)(info_h.height >> 24);
		bmp << (BYTE)(info_h.planes);
		bmp << (BYTE)(info_h.planes >> 8);
		bmp << (BYTE)(info_h.bits);
		bmp << (BYTE)(info_h.bits >> 8);
		bmp << (BYTE)(info_h.compression);
		bmp << (BYTE)(info_h.compression >> 8);
		bmp << (BYTE)(info_h.compression >> 16);
		bmp << (BYTE)(info_h.compression >> 24);
		bmp << (BYTE)(info_h.imagesize);
		bmp << (BYTE)(info_h.imagesize >> 8);
		bmp << (BYTE)(info_h.imagesize >> 16);
		bmp << (BYTE)(info_h.imagesize >> 24);
		bmp << (BYTE)(info_h.xresolution);
		bmp << (BYTE)(info_h.xresolution >> 8);
		bmp << (BYTE)(info_h.xresolution >> 16);
		bmp << (BYTE)(info_h.xresolution >> 24);
		bmp << (BYTE)(info_h.yresolution);
		bmp << (BYTE)(info_h.yresolution >> 8);
		bmp << (BYTE)(info_h.yresolution >> 16);
		bmp << (BYTE)(info_h.yresolution >> 24);
		bmp << (BYTE)(info_h.ncolours);
		bmp << (BYTE)(info_h.ncolours >> 8);
		bmp << (BYTE)(info_h.ncolours >> 16);
		bmp << (BYTE)(info_h.ncolours >> 24);
		bmp << (BYTE)(info_h.importantcolours);
		bmp << (BYTE)(info_h.importantcolours >> 8);
		bmp << (BYTE)(info_h.importantcolours >> 16);
		bmp << (BYTE)(info_h.importantcolours >> 24);

		for(int i = height - 1; i >= 0; i--){
			for(int j = 0; j < width; j++){
				bmp << data[(i * width + j) * 3 + 2];
				bmp << data[(i * width + j) * 3 + 1];
				bmp << data[(i * width + j) * 3 + 0];
			}
			for(int j = 0; j < offset; j++){
				bmp << 0x00;
			}
		}
		bmp.close();
	}
}
void RawToBmpGray(string filename, std::vector<BYTE> &data, int width, int height)
{
	filename += ".bmp";
	fstream bmp;
	bmp.open(filename, ios::binary | ios::out);
	if(!bmp)
	{
		cout << "unable to build image from bmp" << endl;
		exit(1);
	}
	else
	{
		int storeW = (width * 3 + 3);
		storeW /= 4;
		storeW *= 4;

		int offset = storeW - width * 3;

		FILE_HEADER file_h;
		file_h.type = 0x424D;
		file_h.size = (DWORD)(14 + sizeof(INFO_HEADER) + storeW * height);
		file_h.reserved1 = 0x0000;
		file_h.reserved2 = 0x0000;
		file_h.offset = (DWORD)(14 + sizeof(INFO_HEADER));

		bmp << (BYTE)(file_h.type >> 8);
		bmp << (BYTE)(file_h.type);
		bmp << (BYTE)(file_h.size);
		bmp << (BYTE)(file_h.size >> 8);
		bmp << (BYTE)(file_h.size >> 16);
		bmp << (BYTE)(file_h.size >> 24);
		bmp << (BYTE)(file_h.reserved1);
		bmp << (BYTE)(file_h.reserved1 >> 8);
		bmp << (BYTE)(file_h.reserved2);
		bmp << (BYTE)(file_h.reserved2 >> 8);
		bmp << (BYTE)(file_h.offset);
		bmp << (BYTE)(file_h.offset >> 8);
		bmp << (BYTE)(file_h.offset >> 16);
		bmp << (BYTE)(file_h.offset >> 24);

		INFO_HEADER info_h;
		info_h.size = sizeof(INFO_HEADER);
		info_h.width = width;
		info_h.height = height;
		info_h.planes = (WORD)1;
		info_h.bits = (WORD)24;
		info_h.compression = 0;
		info_h.imagesize = storeW * height;
		info_h.xresolution = 0;
		info_h.yresolution = 0;
		info_h.ncolours = 0;
		info_h.importantcolours = 0;

		bmp << (BYTE)(info_h.size);
		bmp << (BYTE)(info_h.size >> 8);
		bmp << (BYTE)(info_h.size >> 16);
		bmp << (BYTE)(info_h.size >> 24);
		bmp << (BYTE)(info_h.width);
		bmp << (BYTE)(info_h.width >> 8);
		bmp << (BYTE)(info_h.width >> 16);
		bmp << (BYTE)(info_h.width >> 24);
		bmp << (BYTE)(info_h.height);
		bmp << (BYTE)(info_h.height >> 8);
		bmp << (BYTE)(info_h.height >> 16);
		bmp << (BYTE)(info_h.height >> 24);
		bmp << (BYTE)(info_h.planes);
		bmp << (BYTE)(info_h.planes >> 8);
		bmp << (BYTE)(info_h.bits);
		bmp << (BYTE)(info_h.bits >> 8);
		bmp << (BYTE)(info_h.compression);
		bmp << (BYTE)(info_h.compression >> 8);
		bmp << (BYTE)(info_h.compression >> 16);
		bmp << (BYTE)(info_h.compression >> 24);
		bmp << (BYTE)(info_h.imagesize);
		bmp << (BYTE)(info_h.imagesize >> 8);
		bmp << (BYTE)(info_h.imagesize >> 16);
		bmp << (BYTE)(info_h.imagesize >> 24);
		bmp << (BYTE)(info_h.xresolution);
		bmp << (BYTE)(info_h.xresolution >> 8);
		bmp << (BYTE)(info_h.xresolution >> 16);
		bmp << (BYTE)(info_h.xresolution >> 24);
		bmp << (BYTE)(info_h.yresolution);
		bmp << (BYTE)(info_h.yresolution >> 8);
		bmp << (BYTE)(info_h.yresolution >> 16);
		bmp << (BYTE)(info_h.yresolution >> 24);
		bmp << (BYTE)(info_h.ncolours);
		bmp << (BYTE)(info_h.ncolours >> 8);
		bmp << (BYTE)(info_h.ncolours >> 16);
		bmp << (BYTE)(info_h.ncolours >> 24);
		bmp << (BYTE)(info_h.importantcolours);
		bmp << (BYTE)(info_h.importantcolours >> 8);
		bmp << (BYTE)(info_h.importantcolours >> 16);
		bmp << (BYTE)(info_h.importantcolours >> 24);

		double gray = 0.0;
		for(int i = height - 1; i >= 0; i--)
		{
			for(int j = 0; j < width; j++)
			{
				gray  = 0.299 * (double)data[(i * width + j) * 3 + 0];
				gray += 0.587 * (double)data[(i * width + j) * 3 + 1];
				gray += 0.114 * (double)data[(i * width + j) * 3 + 2];
				bmp << (unsigned char)gray;
				bmp << (unsigned char)gray;
				bmp << (unsigned char)gray;
			}
			for(int j = 0; j < offset; j++)
			{
				bmp << 0x00;
			}
		}

		bmp.close();
	}
}