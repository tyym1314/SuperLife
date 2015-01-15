//
//  SceneConst.h
//  SuperLife
//
//  Created by wang haibo on 14-8-4.
//
//

#ifndef SuperLife_SceneConst_h
#define SuperLife_SceneConst_h

///图层掩码
static const int LAYER_HIDEN               = 0<<1;            ///隐藏层
static const int LAYER_BACKGROUND          = 1<<1;            ///背景层
static const int LAYER_BACKGROUND_EFFECT   = 2<<1;            ///背景特效层
static const int LAYER_TERRAIN             = 3<<1;            ///地表网格层
static const int LAYER_BASE                = 4<<1;            ///基本层
static const int LAYER_EFFECT              = 5<<1;            ///特效层
static const int LAYER_SCREEN_EFFECT       = 6<<1;            ///屏幕特效层
static const int LAYER_UI                  = 7<<1;            ///UI层
static const int LAYER_CONSOLE             = 8<<1;            ///控制台层
static const int LAYER_DEBUG_INFO          = 9<<1;            ///调试信息层

static const int LAYER_ALL = LAYER_HIDEN | LAYER_BACKGROUND | LAYER_BACKGROUND_EFFECT | LAYER_TERRAIN
                            | LAYER_BASE | LAYER_EFFECT | LAYER_SCREEN_EFFECT | LAYER_UI
                            | LAYER_CONSOLE| LAYER_DEBUG_INFO;


///场景ID
static const int SCENE_MENU                             = 1;        ///Menu界面

static const int SCENE_MAIN                             = 10;       ///主界面
static const int SCENE_MISSION_LIST                     = 11;       ///任务列表界面
static const int SCENE_MISSION                          = 12;       ///任务界面
static const int SCENE_EDITOR                           = 13;       ///编辑器界面
static const int SCENE_SHOP                             = 14;       ///商店界面
static const int SCENE_HELPINFO                         = 15;       ///帮助说明界面
static const int SCENE_LEVELEDITOR                      = 16;       ///任务编辑界面

#endif
