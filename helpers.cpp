#include "helpers.h"

ray_tracer::Texture ReadTextureFromPPX(std::string filename) {
  auto image = net_bpm_image::MakePPMImage(filename.c_str());
  auto texture = ray_tracer::Texture(image->Width(), image->Height());
  for (int y = 0; y < image->Width(); ++y) {
    for (int x = 0; x < image->Height(); ++x) {
      auto color = image->Get(x, y);
      texture.Set(x, y, {color.r / 255, color.g / 255, color.b / 255});
    }
  }
  return texture;
}

ray_tracer::CubemapTextures ReadCubemapTexturesFromDir(std::string dirname) {
  std::filesystem::path dir(dirname);

  auto output = ray_tracer::CubemapTextures{
      ReadTextureFromPPX((dir / "front.ppx").string()),
      ReadTextureFromPPX((dir / "right.ppx").string()),
      ReadTextureFromPPX((dir / "back.ppx").string()),
      ReadTextureFromPPX((dir / "left.ppx").string()),
      ReadTextureFromPPX((dir / "top.ppx").string()),
      ReadTextureFromPPX((dir / "bottom.ppx").string())};

  return output;
}