#include <Geode/Geode.hpp>
#include <Geode/modify/CCImage.hpp>

#include <asp/data.hpp>

#include <manager.hpp>
#include <formats.hpp>
#include <ccimageext.hpp>
#include <crc32.hpp>

using namespace geode::prelude;
using blaze::CCImageExt;

class $modify(CCImage) {
    CCImageExt* ext() {
        return static_cast<CCImageExt*>(static_cast<CCImage*>(this));
    }

    static void onModify(auto& self) {
        // run last since we dont call the originals
        (void) self.setHookPriority("cocos2d::CCImage::initWithImageFile", 9999999).unwrap();
        (void) self.setHookPriority("cocos2d::CCImage::initWithImageFileThreadSafe", 9999999).unwrap();
        (void) self.setHookPriority("cocos2d::CCImage::_initWithPngData", 9999999).unwrap();
    }

    bool initWithImageFileCommon(uint8_t* buffer, size_t size, EImageFormat format, const char* path) {
        // if not png, just do the default impl of this func
        if (format != CCImage::EImageFormat::kFmtPng && !std::string_view(path).ends_with(".png")) {
            return CCImage::initWithImageData(buffer, size);
        }

        auto res = this->ext()->initWithSPNGOrCache(buffer, size, path);
        if (res) {
            return true;
        } else {
            log::warn("Failed to load image ({}) at path {}", res.unwrapErr(), path);
            return false;
        }
    }

    $override
    bool initWithImageFile(const char* path, EImageFormat format) {
        size_t size = 0;

        auto buffer = LoadManager::get().readFile(path, size);

        if (!buffer || size == 0) {
            return false;
        }

        return this->initWithImageFileCommon(buffer.get(), size, format, path);
    }

    $override
    bool initWithImageFileThreadSafe(const char* path, EImageFormat format) {
        return this->initWithImageFile(path, format); // who cares about thread safety?
    }

    $override
    bool _initWithPngData(void* data, int size) {
        auto res = this->ext()->initWithSPNG(data, size);
        if (!res) {
            log::warn("{}", res.unwrapErr());
            return false;
        }

        return true;
    }
};
