#include "net_bpm_image.h"

#include <vector>
#include <fstream>
#include <iostream>
#include <assert.h>
#include <mutex>
#include <shared_mutex>

namespace net_bpm_image {

class PPMImage
    : public INetBpmImage {
 public:
  PPMImage(size_t w, size_t h)
      : w_(w), h_(h), data_(w, std::vector<Color>(h, {0, 1, 0})) {
  }

  explicit PPMImage(const char* filename) {
    std::ifstream fin(filename);
    std::string type, tmp_buffer;
    fin >> type;
    assert(type == "P3" || type == "P6");
    fin >> w_ >> h_;
    fin >> tmp_buffer;
    assert(tmp_buffer == "255");
    data_ = std::vector<std::vector<Color>>(w_, std::vector<Color>(h_));
    if (type == "P3") {
      ReadP3(fin);
    } else {
      ReadP6(fin);
    }
  }

  void Set(int x, int y, Color c) override {
    std::unique_lock<std::shared_mutex> lock(mutex_);
    assert(0 <= x && x < w_);
    assert(0 <= y && y < h_);
    data_[x][y] = c;
  }

  Color Get(int x, int y) override {
    std::unique_lock<std::shared_mutex> lock(mutex_);
    assert(0 <= x && x < w_);
    assert(0 <= y && y < h_);
    return data_[x][y];
  }

  int Width() const override {
    std::shared_lock<std::shared_mutex> lock(mutex_);
    return w_;
  }

  int Height() const override {
    std::shared_lock<std::shared_mutex> lock(mutex_);
    return h_;
  }

  void Save(const std::string filename) override {
    std::unique_lock<std::shared_mutex> lock(mutex_);
    std::ofstream fout(filename);

    fout << "P3"
         << "\n";
    fout << w_ << " " << h_ << "\n";
    fout << 255 << "\n";
    for (int y = 0; y < h_; ++y) {
      for (int x = 0; x < w_; ++x) {
        PrintPixel(fout, data_[x][y]);
      }
    }

    fout << std::flush;
  }

 private:
  void ReadP3(std::istream& fin) {
    for (int y = 0; y < h_; ++y) {
      for (int x = 0; x < w_; ++x) {
        fin >> data_[x][y].r >> data_[x][y].g >> data_[x][y].b;
      }
    }
  }

  void ReadP6(std::istream& fin) {
    for (int y = 0; y < h_; ++y) {
      for (int x = 0; x < w_; ++x) {
        uint8_t r, g, b;
        fin >> std::noskipws >> b >> r >> g;
        data_[x][y] = {r / 255., g / 255., b / 255.};
      }
    }
  }

  void PrintPixel(std::ostream& out, Color color) {
    PrintSubPixel(out, color.r);
    PrintSubPixel(out, color.g);
    PrintSubPixel(out, color.b);
  }
  void inline PrintSubPixel(std::ostream& out, double sub_color) {
    out << std::max(0, std::min(255, (int)(sub_color * 255))) << " ";
  }

 private:
  size_t w_, h_;

  mutable std::shared_mutex mutex_;
  std::vector<std::vector<Color>> data_;
};

INetBpmImagePtr MakePPMImage(size_t w, size_t h) {
  return std::make_shared<PPMImage>(w, h);
}

INetBpmImagePtr MakePPMImage(const char* filename) {
  return std::make_shared<PPMImage>(filename);
}

}