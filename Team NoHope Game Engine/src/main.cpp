#include "Game.h"
#include "Window.h"
#include "Util.h"

//_________________________________________________________________________________

int main()
{
	NoHope::Window* window = new NoHope::Window(1280, 720, "NoHope");
	Game* game = new Game(1280, 720);  //pelialueen koko t:Jesse
	float dt = 0.0f;
	float oldTime = 0.0f;
	float newTime = 0.0f;

	while (window->isOpen())
	{
		oldTime = newTime;
		newTime = NoHope::Util::getTotalTime();
		dt = newTime - oldTime;
	
		game->update(dt);
		game->render();
		window->pollEvents();
		
	}
//_________________________________________________________________________________
    //GLenum err = glewInit();
    //if (GLEW_OK != err)
    //{
    //    /* Problem: glewInit failed, something is seriously wrong. */
    //    fprintf( stderr, "Error: %s\n", glewGetErrorString(err) );
    //    exit( EXIT_FAILURE );
    //}
    //fprintf( stderr, "Using GLEW %s\n", glewGetString(GLEW_VERSION) );

	//int fontDataSize;
	//GLubyte* fontData = NoHope::Util::loadBinary(NoHope::Util::resourcePath + "fonts/Vera.ttf",fontDataSize);

    //texture_atlas_t * atlas = texture_atlas_new( 1024, 1024, 1 );
    //const char *filename = "fonts/Vera.ttf";
    //const wchar_t *cache = L" !\"#$%&'()*+,-./0123456789:;<=>?"
                         //  L"@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_"
                         //  L"`abcdefghijklmnopqrstuvwxyz{|}~";
    //size_t minsize = 8, maxsize = 27;
    //size_t count = maxsize - minsize;
    //size_t i, missed = 0;
	
    //for( i=minsize; i < maxsize; ++i )
    //{
		//Load font
      //  texture_font_t * font = texture_font_new_from_memory( atlas, 16, fontData, fontDataSize);
        //missed += texture_font_load_glyphs( font, cache );
        //texture_font_delete( font );
    //}

    //printf( "Matched font               : %s\n", filename );
    //printf( "Number of fonts            : %ld\n", count );
    //printf( "Number of glyphs per font  : %ld\n", wcslen(cache) );
    //printf( "Number of missed glyphs    : %ld\n", missed );
   // printf( "Total number of glyphs     : %ld/%ld\n",
     //       wcslen(cache)*count - missed, wcslen(cache)*count );
    //printf( "Texture size               : %ldx%ld\n", atlas->width, atlas->height );
    //printf( "Texture occupancy          : %.2f%%\n", 
      //      100.0*atlas->used/(float)(atlas->width*atlas->height) );

    //glClearColor(1,1,1,1);
    //glEnable( GL_BLEND );
    //glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    //glEnable( GL_TEXTURE_2D );
    //glBindTexture( GL_TEXTURE_2D, atlas->id );

    //typedef struct { float x,y,z, u,v, r,g,b,a; } vertex_t;
    //vertex_t vertices[4] =  {
       // {  0, 0, 0, 0,1, 0,0,0,1},
      //  {  0,512,0, 0,0, 0,0,0,1},
      //  {512,512,0, 1,0, 0,0,0,1},
     //   {512,  0,0, 1,1, 0,0,0,1} };
    //GLuint indices[6] = { 0, 1, 2, 0,2,3 };
    //buffer = vertex_buffer_new( "vertex:3f,tex_coord:2f,color:4f" );
    //vertex_buffer_push_back( buffer, vertices, 4, indices, 6 );

	//shader = shader_load("Shaders/v3f-t2f-c4f.vert",
	//						"Shaders/v3f-t2f-c4f.frag");
	//NoHope::Shader* shader;
	//shader = new NoHope::Shader("Shaders/v3f-t2f-c4f.vert","Shaders/v3f-t2f-c4f.frag");
    //mat4_set_identity( &projection );
    //mat4_set_identity( &model );
    //mat4_set_identity( &view );
    return 0;
}
