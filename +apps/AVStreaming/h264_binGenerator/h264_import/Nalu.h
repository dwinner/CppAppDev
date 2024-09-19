#ifndef H264_NALPARSERSAMPLE_NALUNITTYPE_H
#define H264_NALPARSERSAMPLE_NALUNITTYPE_H

#include <array>
#include <utility>
#include <valarray>

class Nalu
{
public:
    explicit Nalu()
        : length_(0)
        , content_(std::valarray<uint8_t>(0))
    {
    }

    explicit Nalu(const size_t length, std::valarray<uint8_t> content)
        : length_(length)
        , content_(std::move(content))
    {
    }

    Nalu(const Nalu& other)
        : length_ { other.length_ }
        , content_ { other.content_ }
    {
    }

    Nalu(Nalu&& other) noexcept
        : length_ { other.length_ }
        , content_ { std::move(other.content_) }
    {
    }

    Nalu& operator=(Nalu other)
    {
        std::swap(*this, other);
        return *this;
    }

    size_t GetLength() const
    {
        return length_;
    }

    std::valarray<uint8_t> GetContent() const
    {
        return content_;
    }

private:
    size_t length_;
    std::valarray<uint8_t> content_;
};

#endif // H264_NALPARSERSAMPLE_NALUNITTYPE_H
