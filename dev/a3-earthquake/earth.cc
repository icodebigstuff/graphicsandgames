/** CSci-4611 Assignment 3:  Earthquake
 */

#include "earth.h"
#include "config.h"

#include <vector>

// for M_PI constant
#define _USE_MATH_DEFINES
#include <math.h>


Earth::Earth() {
}

Earth::~Earth() {
}

bool sphere = true;
int now = 0;
int next = 0;
int count = 0;



const int nslices = 10;
const int nstacks = 10;

void Earth::Init(const std::vector<std::string>& search_path) {
    // init shader program
    shader_.Init();

    // init texture: you can change to a lower-res texture here if needed
    earth_tex_.InitFromFile(Platform::FindFile("earth-2k.png", search_path));


    int x = nslices;
    int y = nstacks;
    int xy = x * y;
    // TODO: This is where you need to set the vertices and indiceds for earth_mesh_.

    // As a demo, we'll add a square with 2 triangles.
    std::vector<unsigned int> indices;
    std::vector<Point2> text_cor;
    std::vector<Point3> vertices;
    std::vector<Vector3> normals;


    float latitude;
    float longitude;


    for (int y = 0; y <= nslices; y++) {
        for (int x = 0; x <= nstacks; x++) {

            longitude = GfxMath::Lerp(-GfxMath::PI, GfxMath::PI, (float)y / nslices); //-pi to pi
            latitude = GfxMath::Lerp(-GfxMath::PI / 2, GfxMath::PI / 2, (float)x / nstacks); // -pi/2 to pi/2
            if (getGlobe() == true) {
                Point3 sphere1 = LatLongToSphere(latitude, longitude);
                vertices.push_back(LatLongToSphere(latitude, longitude));
                Vector3 normal = Vector3(cos(latitude) * sin(longitude), sin(latitude), cos(latitude) * cos(longitude));
                normals.push_back(normal);
            }
            else {
                Point3 plane = LatLongToPlane(latitude, longitude);
                vertices.push_back(plane);
            }

            text_cor.push_back(Point2((float)y / nslices, 1 - (float)x / nstacks));

        }
    }


    for (int i = 0; i < nslices; i++){
        for (int j = 0; j < nstacks; j++) {
            int base = (nstacks + 1) * i + j;
            indices.push_back(base);
            indices.push_back(base + y + 1);
            indices.push_back(base +1);
            
            indices.push_back(base + 1);
            indices.push_back(base + y + 1);
            indices.push_back(base + y + 2);
 
        }
    }


    earth_mesh_.SetTexCoords(0,text_cor);
    earth_mesh_.SetVertices(vertices);
    earth_mesh_.SetIndices(indices);
    earth_mesh_.SetNormals(normals);
    earth_mesh_.UpdateGPUMemory();



    /**
    vertices.push_back(Point3(0, 0, 0));
    vertices.push_back(Point3(1, 0, 0));
    vertices.push_back(Point3(1, 1, 0));
    vertices.push_back(Point3(0, 1, 0));
    // indices into the arrays above for the first triangl */
    /* indices.push_back(0);
     indices.push_back(1);
     indices.push_back(2);

     // indices for the second triangle, note some are reused
     indices.push_back(0);
     indices.push_back(2);
     indices.push_back(3); */
     /**
     indices.push_back(4);
     indices.push_back(5);
     indices.push_back(6);

     // indices for the second triangle, note some are reused
     indices.push_back(4);
     indices.push_back(6);
     indices.push_back(7); */



}

void Earth::Switch() {

    std::vector<Point3> vertices;
    std::vector<Vector3> normals;


    float latitude;
    float longitude;
    if (count % 2 == 0) {
        setGlobe(true);
        count = count + 1;
    }
    else {
        setGlobe(false);
        count = 0;
    }


    for (int y = 0; y <= nslices; y++) {
        for (int x = 0; x <= nstacks; x++) {

            longitude = GfxMath::Lerp(-GfxMath::PI, GfxMath::PI, (float)y / nslices); //-pi to pi
            latitude = GfxMath::Lerp(-GfxMath::PI / 2, GfxMath::PI / 2, (float)x / nstacks); // -pi/2 to pi/2
            if (getGlobe() == true) {
                Point3 sphere1 = LatLongToSphere(latitude, longitude);
                vertices.push_back(LatLongToSphere(latitude, longitude));
                Vector3 normal = Vector3(cos(latitude) * sin(longitude), sin(latitude), cos(latitude) * cos(longitude));
                normals.push_back(normal);
            }
            else {
                Point3 plane = LatLongToPlane(latitude, longitude);
                vertices.push_back(plane);
            }


        }
    }

    earth_mesh_.SetVertices(vertices);

    earth_mesh_.SetNormals(normals);
    earth_mesh_.UpdateGPUMemory();

}


void Earth::Draw(const Matrix4 &model_matrix, const Matrix4 &view_matrix, const Matrix4 &proj_matrix) {
    // Define a really bright white light.  Lighting is a property of the "shader"
    DefaultShader::LightProperties light;
    light.position = Point3(10,10,10);
    light.ambient_intensity = Color(1,1,1);
    light.diffuse_intensity = Color(1,1,1);
    light.specular_intensity = Color(1,1,1);
    shader_.SetLight(0, light);

    // Adust the material properties, material is a property of the thing
    // (e.g., a mesh) that we draw with the shader.  The reflectance properties
    // affect the lighting.  The surface texture is the key for getting the
    // image of the earth to show up.
    DefaultShader::MaterialProperties mat;
    mat.ambient_reflectance = Color(0.5, 0.5, 0.5);
    mat.diffuse_reflectance = Color(0.75, 0.75, 0.75);
    mat.specular_reflectance = Color(0.75, 0.75, 0.75);
    mat.surface_texture = earth_tex_;

    // Draw the earth mesh using these settings
    if (earth_mesh_.num_triangles() > 0) {
        shader_.Draw(model_matrix, view_matrix, proj_matrix, &earth_mesh_, mat);
    }
}


Point3 Earth::LatLongToSphere(double latitude, double longitude) const {
    // TODO: We recommend filling in this function to put all your
    // lat,long --> sphere calculations in one place.

    return Point3(cos(latitude) * sin(longitude), sin(latitude), cos(latitude) * cos(longitude));
}

Point3 Earth::LatLongToPlane(double latitude, double longitude) const {
    // TODO: We recommend filling in this function to put all your
    // lat,long --> plane calculations in one place.
     return Point3(longitude, latitude, 0);
}



void Earth::DrawDebugInfo(const Matrix4 &model_matrix, const Matrix4 &view_matrix, const Matrix4 &proj_matrix) {
    // This draws a cylinder for each line segment on each edge of each triangle in your mesh.
    // So it will be very slow if you have a large mesh, but it's quite useful when you are
    // debugging your mesh code, especially if you start with a small mesh.
    for (int t=0; t<earth_mesh_.num_triangles(); t++) {
        std::vector<unsigned int> indices = earth_mesh_.read_triangle_indices_data(t);
        std::vector<Point3> loop;
        loop.push_back(earth_mesh_.read_vertex_data(indices[0]));
        loop.push_back(earth_mesh_.read_vertex_data(indices[1]));
        loop.push_back(earth_mesh_.read_vertex_data(indices[2]));
        quick_shapes_.DrawLines(model_matrix, view_matrix, proj_matrix,
            Color(1,1,0), loop, QuickShapes::LinesType::LINE_LOOP, 0.005f);
    }
}

