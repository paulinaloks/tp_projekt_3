#include "planar_quadrotor_visualizer.h"
PlanarQuadrotorVisualizer::PlanarQuadrotorVisualizer(PlanarQuadrotor *quadrotor_ptr): quadrotor_ptr(quadrotor_ptr) {
}
/**
 * TODO: Improve visualizetion
 * 1. Transform coordinates from quadrotor frame to image frame so the circle is in the middle of the screen
 * 2. Use more shapes to represent quadrotor (e.x. try replicate http://underactuated.mit.edu/acrobot.html#section3 or do something prettier)
 * 3. Animate proppelers (extra points)
 */
void drawRectangle(SDL_Renderer* renderer, int x, int y, int width, int height) {
    
    SDL_Rect rect = {x, y, width, height};
    SDL_SetRenderDrawColor(renderer, 170, 40, 170, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer, &rect);
    SDL_RenderPresent(renderer);
}
void PlanarQuadrotorVisualizer::render(std::shared_ptr<SDL_Renderer> &gRenderer, int t) {
    Eigen::VectorXf state = quadrotor_ptr->GetState();
    float q_x, q_y, theta;
    /* x, y, theta coordinates */
    q_x=state[0];
    q_y=state[1];
    theta = state[2];
    SDL_SetRenderDrawColor(gRenderer.get(), 0xFF, 0x00, 0x00, 0xFF);
    int width=128;
    int height=32;
    int s_width=64;
    int s_height=16;
    Sint16 vx[4];
    Sint16 vy[4];
    Sint16 px[4];
    Sint16 py[4];
    Sint16 lx[4];
    Sint16 ly[4];
    vx[0]=q_x -cos(theta)*(width/2) + sin(theta) * (height /2);
    vx[1]=q_x-cos(theta)*(width/2)-sin(theta) * (height /2);
    vx[2]=q_x+cos(theta)*(width/2)- sin(theta) * (height /2);
    vx[3]=q_x+cos(theta)*(width/2)+ sin(theta) * (height /2);
    vy[0]=q_y+cos(theta)*(height /2)+sin(theta) *(width/2) ;
    vy[1]=q_y-cos(theta)*(height /2)+sin(theta) * (width/2);
    vy[2]=q_y-cos(theta)*(height /2)-sin(theta) * (width/2);
    vy[3]=q_y+cos(theta)*(height /2)-sin(theta) * (width/2);

    lx[0]=vx[1]+sin(t)*cos(theta)*(s_width/2) + sin(theta) * (s_height /2)-sin(theta)*s_height/2;
    lx[1]=vx[1]+sin(t)*cos(theta)*(s_width/2) - sin(theta) * (s_height /2)-sin(theta)*s_height/2;
    lx[2]=vx[1]-sin(t)*cos(theta)*(s_width/2) - sin(theta) * (s_height /2)-sin(theta)*s_height/2;
    lx[3]=vx[1]-sin(t)*cos(theta)*(s_width/2) + sin(theta) * (s_height /2)-sin(theta)*s_height/2;
    ly[0]=vy[1]+cos(theta)*(s_height/2)-sin(t)*sin(theta) *(s_width/2) - cos(theta)*s_height/2 ;
    ly[1]=vy[1]-cos(theta)*(s_height/2)-sin(t)*sin(theta) *(s_width/2) - cos(theta)*s_height/2 ;
    ly[2]=vy[1]-cos(theta)*(s_height/2)+sin(t)*sin(theta) *(s_width/2) - cos(theta)*s_height/2 ;
    ly[3]=vy[1]+cos(theta)*(s_height/2)+sin(t)*sin(theta) *(s_width/2) - cos(theta)*s_height/2 ;

    px[0]=vx[2]+sin(t)*cos(theta)*(s_width/2) + sin(theta) * (s_height /2)-sin(theta)*s_height/2;
    px[1]=vx[2]+sin(t)*cos(theta)*(s_width/2) - sin(theta) * (s_height /2)-sin(theta)*s_height/2;
    px[2]=vx[2]-sin(t)*cos(theta)*(s_width/2) - sin(theta) * (s_height /2)-sin(theta)*s_height/2;
    px[3]=vx[2]-sin(t)*cos(theta)*(s_width/2) + sin(theta) * (s_height /2)-sin(theta)*s_height/2;
    py[0]=vy[2]+cos(theta)*(s_height/2)-sin(t)*sin(theta) *(s_width/2) - cos(theta)*s_height/2 ;
    py[1]=vy[2]-cos(theta)*(s_height/2)-sin(t)*sin(theta) *(s_width/2) - cos(theta)*s_height/2 ;
    py[2]=vy[2]-cos(theta)*(s_height/2)+sin(t)*sin(theta) *(s_width/2) - cos(theta)*s_height/2 ;
    py[3]=vy[2]+cos(theta)*(s_height/2)+sin(t)*sin(theta) *(s_width/2) - cos(theta)*s_height/2 ;

    // lx[0]=vx[0]-s_width/2;
    // lx[1]=vx[1]-s_width/2;
    // lx[2]=vx[2]-3*s_width/2;
    // lx[3]=vx[3]-3*s_width/2;
    // ly[0]=vy[0]-2*s_height;
    // ly[1]=vy[1]-s_height;
    // ly[2]=vy[2]-s_height;
    // ly[3]=vy[3]-2*s_height;
    

    filledPolygonColor(gRenderer.get(),vx,vy, 4 ,0xFF991199);
    filledPolygonColor(gRenderer.get(),lx,ly, 4 ,0xAA555555);
    filledPolygonColor(gRenderer.get(),px,py, 4 ,0xAA555555);
   
}