# Ray Tracer <!-- omit in toc -->

A Ray Tracer made by Isard Botha for fun.

- [Images](#images)
  - [Starting point](#starting-point)
- [| Primitives  | 4        |](#-primitives---4--------)
  - [Full BSDF](#full-bsdf)
- [| Primitives  | 9         |](#-primitives---9---------)
  - [Basic Algorithm Small Light Source](#basic-algorithm-small-light-source)
- [| Primitives  | 9       |](#-primitives---9-------)
  - [BVH](#bvh)
- [| Primitives  | 2161     |](#-primitives---2161-----)
- [Initial Path-Tracing Algorithm](#initial-path-tracing-algorithm)
- [Material](#material)
- [BVH](#bvh-1)
- [Resources](#resources)

## Images

### Starting point
![Image of the day|2022 02 21](./Ray-Tracer/output/outCamera220221.png)
| Name        | Value    |
| ----------- | -------- |
| Resolution  | 1080x607 |
| Render Time | 30 mins  |
| SPP         | 256      |
| Primitives  | 4        |
-----------------------

### Full BSDF
![Full BSDF](./Ray-Tracer/output/outFullBSDF.jpeg)

| Name        | Value     |
| ----------- | --------- |
| Resolution  | 1920x1080 |
| Render Time | 30 mins   |
| SPP         | 256       |
| Primitives  | 9         |
-----------------------

### Basic Algorithm Small Light Source
![Small Light](./Ray-Tracer/output/SmallerLightSource.png)

| Name        | Value   |
| ----------- | ------- |
| Resolution  | 512x288 |
| Render Time | 4 mins  |
| SPP         | 512     |
| Primitives  | 9       |
-----------------------

### BVH
![Small Light](./Ray-Tracer/output/BVHDemo.png)

| Name        | Value    |
| ----------- | -------- |
| Resolution  | 1080x607 |
| Render Time | 10 mins  |
| SPP         | 512      |
| Primitives  | 2161     |
-----------------------

## Initial Path-Tracing Algorithm

The starting algorithm here leans heavily on monte-carlo integration. In essense we cast a large amount of rays which all scatter based on probabilities defined by the material. As more samples are taken we converge on the true look of the image.

The image rendered this way only converges quickly if there is a high chance of hitting the light source (The sky in this case). If there is a smaller light source the image remains very noisy.

## Material

This ray-tracer utilizes a universal material that considers the following properties.

Colours
* diffuse
*	emission
*	specular
*	reflective
*	ambient
*	transparent

Scalars
*	shininess
*	shininess_strength
*	shininess_tint
*	reflectivity
*	refraction_index
*	transmission

The material amounts to a scatter function which takes an incoming ray, and information about the collision. It returns an attenuation (how the incoming light is absorbed) and a scattered ray.

## BVH

The first major optimisation was Bounding Volume Heirarchy. I collect all objects into a bounding volume and build a tree of sub-volumes based by recursively splitting the objects in half along a random axis. This alows me to only collide with the objects I need to.

## Resources

[Ray Tracing In One Weekend](https://raytracing.github.io/)