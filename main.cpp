#include "proj.hpp"

///todo eventually
///split into dynamic and static objects

///todo
///fix memory management to not be atrocious

///we're completely hampered by memory latency

///move to two eye rendering and optimise for that instead, do duel view render at once
int main(int argc, char *argv[])
{
    ///remember to make g_arrange_mem run faster!

    sf::Clock load_time;

    objects_container sponza;

    sponza.set_file("sp2/sp2.obj");
    //sponza.set_file("sp2/cornellfixed.obj");
    sponza.set_active(true);
    sponza.cache = false;

    engine window;

    window.load(2048,2048,1000, "turtles", "cl2.cl");

    window.set_camera_pos((cl_float4){-800,150,-570});

    //window.window.setVerticalSyncEnabled(false);

    ///write a opencl kernel to generate mipmaps because it is ungodly slow?
    ///Or is this important because textures only get generated once, (potentially) in parallel on cpu?

    obj_mem_manager::load_active_objects();

    //sponza.scale(400.0f);

    texture_manager::allocate_textures();

    obj_mem_manager::g_arrange_mem();
    obj_mem_manager::g_changeover();

    sf::Event Event;

    light l;
    l.set_col((cl_float4){0.0f, 1.0f, 0.0f, 0.0f});
    l.set_shadow_casting(1);
    l.set_brightness(1);
    l.set_pos((cl_float4){-200, 100, 0});
    //l.set_pos((cl_float4){-150, 150, 300});
    l.radius = 100000;
    /*l.set_pos((cl_float4){-200, 2000, -100, 0});
    l.set_pos((cl_float4){-200, 200, -100, 0});
    l.set_pos((cl_float4){-400, 150, -555, 0});*/
    window.add_light(&l);

    l.set_col((cl_float4){1.0f, 0.0f, 1.0f, 0});

    l.set_pos((cl_float4){-0, 200, -500, 0});
    l.shadow = 1;
    l.radius = 100000;

    window.add_light(&l);

    //window.set_camera_pos({0, 100, 200});
    //window.set_camera_rot({0.1, M_PI, 0});

    /*l.set_col({1.0, 0.5, 0.0});
    l.set_pos((cl_float4){-0, 2000,-0, 0});
    l.set_shadow_casting(1);

    window.add_light(&l);

    l.set_col({0, 0.5, 0.99});
    l.set_pos((cl_float4){-1200, 250,0, 0});
    l.set_shadow_casting(1);

    window.add_light(&l);*/


    window.construct_shadowmaps();

    int times[10] = {0};
    int time_count = 0;

    int load_first = 0;

    while(window.window.isOpen())
    {
        sf::Clock c;

        if(window.window.pollEvent(Event))
        {
            if(Event.type == sf::Event::Closed)
                window.window.close();
        }

        window.input();

        window.draw_bulk_objs_n();

        //window.draw_raytrace();

        window.render_buffers();
        window.display();

        times[time_count] = c.getElapsedTime().asMicroseconds();

        time_count = (time_count + 1) % 10;

        int time = 0;

        for(int i=0; i<10; i++)
        {
            time += times[i];
        }

        if(!load_first)
        {
            std::cout << "time to load and execute 1 frame = " << load_time.getElapsedTime().asSeconds();
            load_first = 1;
        }

        std::cout << time/10 << std::endl;

        ///raw time
        //std::cout << c.getElapsedTime().asMicroseconds() << std::endl;
    }
}
