#include "BVHNode.hpp"
#include <Random.h>

BVHNode::BVHNode()
{

}

inline bool box_compare(const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b, int axis) {
    AABB box_a;
    AABB box_b;

    if (!a->GetBounds(box_a) || !b->GetBounds(box_b))
        std::cerr << "No bounding box in bvh_node constructor.\n";

    return box_a.min[axis] < box_b.min[axis];
}

int box_x_compare(const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b) {
    return box_compare(a, b, 0);
}

int box_y_compare(const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b) {
    return box_compare(a, b, 1);
}

int box_z_compare(const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b) {
    return box_compare(a, b, 2);
}

BVHNode::BVHNode(const std::vector<std::shared_ptr<Hittable>>& src_objects, size_t start, size_t end)
{
    auto objects = src_objects; // Create a modifiable array of the source scene objects

    int axis = Random::Int(0, 2);
    auto comparator = (axis == 0) ? box_x_compare
        : (axis == 1) ? box_y_compare
        : box_z_compare;

    size_t object_span = end - start;

    if (object_span == 1) {
        left = right = objects[start];
    }
    else if (object_span == 2) {
        if (comparator(objects[start], objects[start + 1])) {
            left = objects[start];
            right = objects[start + 1];
        }
        else {
            left = objects[start + 1];
            right = objects[start];
        }
    }
    else {
        std::sort(objects.begin() + start, objects.begin() + end, comparator);

        auto mid = start + object_span / 2;
        left = make_shared<BVHNode>(objects, start, mid);
        right = make_shared<BVHNode>(objects, mid, end);
    }

    AABB box_left, box_right;

    if (!left->GetBounds(box_left)
        || !right->GetBounds(box_right)
        )
        std::cerr << "No bounding box in bvh_node constructor.\n";

    box = AABB::SurroundingBox(box_left, box_right);
}

bool BVHNode::Intersect(const Ray& r, HitRecord& rec, float t_min, float t_max) const
{
	if (!box.hit(r, t_min, t_max))
		return false;

	bool hit_left = left->Intersect(r, rec, t_min, t_max);
	bool hit_right = right->Intersect(r, rec, t_min, hit_left ? rec.t : t_max);

	return hit_left || hit_right;
}

bool BVHNode::GetBounds(AABB& output_box) const
{
	output_box = box;
	return true;
}
