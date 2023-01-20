#pragma once

void print(const std::string &s)
{
    if (!po_quiet)
        std::cout << s << '\n';
}

namespace slices
{
    template <typename img_t>
    std::vector<i3d::Image3d<img_t>> get_X(const i3d::Image3d<img_t> &img, std::size_t start_idx, std::size_t end_idx)
    {
        std::vector<i3d::Image3d<img_t>> slices(end_idx - start_idx);
        i3d::Vector3d<std::size_t> slice_size = {img.GetSizeY(), img.GetSizeZ(), 1};

        for (std::size_t i = start_idx; i < end_idx; ++i)
        {
            assert(i < img.GetSliceX());
            slices[i - start_idx].MakeRoom(slice_size);
        }

        for (std::size_t z = 0; z < img.GetSizeZ(); ++z)
            for (std::size_t y = 0; y < img.GetSizeY(); ++y)
                for (std::size_t i = start_idx; i < end_idx; ++i)
                    slices[i - start_idx].SetVoxel(y, z, 1, img.GetVoxel(i, y, z));

        return slices;
    }

    template <typename img_t>
    std::vector<i3d::Image3d<img_t>> get_Y(const i3d::Image3d<img_t> &img, std::size_t start_idx, std::size_t end_idx)
    {
        std::vector<i3d::Image3d<img_t>> slices(end_idx - start_idx);
        i3d::Vector3d<std::size_t> slice_size = {img.GetSizeX(), img.GetSizeZ(), 1};

        for (std::size_t i = start_idx; i < end_idx; ++i)
        {
            assert(i < img.GetSliceY());
            slices[i - start_idx].MakeRoom(slice_size);
        }

        for (std::size_t z = 0; z < img.GetSizeZ(); ++z)
            for (std::size_t i = start_idx; i < end_idx; ++i)
                for (std::size_t x = 0; x < img.GetSizeX(); ++x)
                    slices[i - start_idx].SetVoxel(x, z, 1, img.GetVoxel(x, i, z));

        return slices;
    }

    template <typename img_t>
    std::vector<i3d::Image3d<img_t>> get_Z(const i3d::Image3d<img_t> &img, std::size_t start_idx, std::size_t end_idx)
    {
        std::vector<i3d::Image3d<img_t>> slices(end_idx - start_idx);
        i3d::Vector3d<std::size_t> slice_size = {img.GetSizeX(), img.GetSizeY(), 1};

        for (std::size_t i = start_idx; i < end_idx; ++i)
        {
            assert(i < img.GetSliceZ());
            slices[i - start_idx].MakeRoom(slice_size);
        }

        for (std::size_t i = start_idx; i < end_idx; ++i)
            for (std::size_t y = 0; y < img.GetSizeY(); ++y)
                for (std::size_t x = 0; x < img.GetSizeX(); ++x)
                    slices[i - start_idx].SetVoxel(x, y, 1, img.GetVoxel(x, y, i));

        return slices;
    }

    template <typename img_t>
    void set_X(i3d::Image3d<img_t> &img,
               const std::vector<i3d::Image3d<img_t>> &slices,
               std::size_t start_idx,
               std::size_t end_idx)
    {
        for (std::size_t i = start_idx; i < end_idx; ++i)
        {
            assert(i < img.GetSliceX());
        }

        for (std::size_t z = 0; z < img.GetSizeZ(); ++z)
            for (std::size_t y = 0; y < img.GetSizeY(); ++y)
                for (std::size_t i = start_idx; i < end_idx; ++i)
                    img.SetVoxel(i, y, z, slices[i - start_idx].GetVoxel(y, z, 1));
    }

    template <typename img_t>
    void set_Y(i3d::Image3d<img_t> &img,
               const std::vector<i3d::Image3d<img_t>> &slices,
               std::size_t start_idx,
               std::size_t end_idx)
    {
        for (std::size_t i = start_idx; i < end_idx; ++i)
        {
            assert(i < img.GetSliceY());
        }

        for (std::size_t z = 0; z < img.GetSizeZ(); ++z)
            for (std::size_t i = start_idx; i < end_idx; ++i)
                for (std::size_t x = 0; x < img.GetSizeX(); ++x)
                    img.SetVoxel(x, i, z, slices[i - start_idx].GetVoxel(x, z, 1));
    }

    template <typename img_t>
    void set_Z(i3d::Image3d<img_t> &img,
               const std::vector<i3d::Image3d<img_t>> &slices,
               std::size_t start_idx,
               std::size_t end_idx)
    {
        for (std::size_t i = start_idx; i < end_idx; ++i)
        {
            assert(i < img.GetSliceZ());
        }

        for (std::size_t i = start_idx; i < end_idx; ++i)
            for (std::size_t y = 0; y < img.GetSizeY(); ++y)
                for (std::size_t x = 0; x < img.GetSizeX(); ++x)
                    img.SetVoxel(x, y, i, slices[i - start_idx].GetVoxel(x, y, 1));
    }

}