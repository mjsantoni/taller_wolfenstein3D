//
// Created by andy on 4/12/20.
//

#ifndef TP_WOLFENSTEIN_OBJECTDRAWER_H
#define TP_WOLFENSTEIN_OBJECTDRAWER_H


#include <SDL_render.h>
#include <vector>
#include <map>
#include <limits>
#include "drawing_info.h"
#include "client_wall.h"
#include "image_parser.h"
#include "image_info.h"

class ObjectDrawer {
public:
    ObjectDrawer();
    void initialize(SDL_Renderer* window_renderer, int window_width,
                    int window_height);
    SDL_Texture* drawImage(DrawingInfo& drawing_info, Area& image_area);
    void drawFloor(int x_pos, int wall_posY, int wall_height);
    void drawCeiling(int x_pos, int y_pos);
    void findObjectProportions(DrawingInfo& drawing_info, double distance,
                               double pl_ob_angle, Area& screen_area);
    void getImageInformation(DrawingInfo& drawing_info);
    void getSpriteInformation(DrawingInfo& drawing_info);
    SDL_Texture* drawWall(DrawingInfo& drawing_info, Area& image_area);
    int findXPosForObject(double pl_ob_beta, int object_width);
    int findYPosForObject(int ray_no, double pl_ob_angle, double distance,
                          int object_height);
    int findObjectHeight(double distance, DrawingInfo& drawing_info);
    int findObjectWidth(double distance, DrawingInfo& drawing_info);
    int findRayNumberForAngle(double beta);
    Area assembleScreenArea(int ray_no, DrawingInfo& drawing_info);
    Area assembleScreenArea(DrawingInfo& drawing_info, double distance,
                            double pl_ob_angle);
    int findColumnStartingPoint(int col_height);
    int findColumnHeight(int distance);
    SDL_Texture* drawPlayersWeapon(DrawingInfo& d_i, Area& image_area);
    Area assembleScreenWeaponArea(DrawingInfo& drawing_info);
    void setDistanceInfo(std::map<double, double> _distance_info,
                         std::vector<double> _angles_list);
private:
    SDL_Renderer* renderer;
    int window_width;
    int window_height;
    double width_prop;
    double height_prop;
    std::map<int, std::pair<int, int>> floor_info;
    std::vector<ImageInfo> image_info_vector;
    std::map<double, double> distance_info;
    std::vector<double> angles_list;
    ImageParser image_parser;
    int safe_distance = 30;

    double findWallDistanceForAngle(double angle);
};


#endif //TP_WOLFENSTEIN_OBJECTDRAWER_H