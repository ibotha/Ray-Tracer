#pragma once
#include <Scene/Hittable.hpp>
#include <Scene/HittableList.hpp>

class BVHNode: public Hittable
{
public:
    BVHNode();

    BVHNode(const HittableList& list)
        : BVHNode(list.children, 0, list.children.size())
    {}

    BVHNode(
        const std::vector<std::shared_ptr<Hittable>>& src_objects,
        size_t start, size_t end);

    virtual bool Intersect(const Ray& r, HitRecord & rec, float t_min, float t_max) const override;

    virtual bool GetBounds(AABB& output_box) const override;

public:
    std::shared_ptr<Hittable> left;
    std::shared_ptr<Hittable> right;
    AABB box;
};

