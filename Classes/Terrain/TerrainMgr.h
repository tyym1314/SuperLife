//
//  TerrainMgr.h
//  CCGF
//
//  Created by haibo.wang on 14-3-27.
//
//

#ifndef __CCGF__TerrainMgr__
#define __CCGF__TerrainMgr__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "TerrainCell.h"
class TerrainMgr : public cocos2d::Ref, public cocos2d::extension::ScrollViewDelegate
{
    // 构造函数
    TerrainMgr();
public:
    // 单体
    static TerrainMgr* getInstance();
    // 析构函数
    ~TerrainMgr();
    // 添加地面
    void addTerrain(TerrainCell::CELL_TYPE cell_type, int rows, int columns, float radius, const cocos2d::Point& offset = cocos2d::Vec2(0,0));
    // 删除地面
    void removeTerrain();
    //更新地表单元
    void updateTerrain();
    //重置
    void resetTerrain();
    // 更新处理
    void update(float delta);
    //获取地表单元相邻邻居节点个数
    int getLifeNeighborCount(TerrainCell* cell);
    //获取生命对象代数
    int getGeneration() const;
    //获取生命对象个数
    int getLifeNum() const;
    //获取最小更新频率
    float getMinUpdateDelta() const;
    //获取最大更新频率
    float getMaxUpdateDelta() const;
    //获取当前更新频率
    float getCurUpdateDelta() const;
    //设置当前更新频率
    void setCurUpdateDelta(float curUpdateDelta);
    //获取渲染对象
    cocos2d::DrawNode* getTerrainNode() const { return m_pDrawNode; }
    //获取地形对象位移
    cocos2d::Vec2 getOffset() const { return m_Offset; }
    //加载全部模版
    void loadTemplates(bool simple, bool all);
    //获取指定模版名称
    std::string getTemplateName(ssize_t index);
    //加载模版
    void loadTemplate(const std::string& templateName);
    //保存模版
    void saveTemplate(const std::string& name);
    //删除模版
    void removeTemplate(const std::string& name);
    //获取模版数量
    ssize_t getTemplateCount();
    //是否有次模版
    bool hasTemplate(const std::string& name);
    ///加载选定的模版
    void loadSelectTemplate(ssize_t index);
    ///绘制模版
    void DrawSelectTemplate();
    //保存任务场景
    bool saveLevel(const std::string& levelFileName, const std::string& levelName, const int goalCellNum, const int goalCellGeneration, const int starterCellNum, const int levelType);
    //加载任务场景
    bool loadLevel(const std::string& levelFileName, std::string& levelName, int& goalCellNum, int& goalCellGeneration, int& starterCellNum, int& levelType);
    
    bool isEnableAddTerrainCell() const { return m_bEnableAddTerrainCell; }
    void setEnableAddTerrainCell( bool enableAddTerrainCell ) { m_bEnableAddTerrainCell = enableAddTerrainCell; }
    
    void cacheTerrainCellList();
    void restoreTerrainCellList();
    
    void resetScrollView(bool bAnimate);
    
    virtual void scrollViewDidScroll(cocos2d::extension::ScrollView* view);
    virtual void scrollViewDidZoom(cocos2d::extension::ScrollView* view);
public:
    // 处理输入
    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    virtual void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unused_event);
private:
    cocos2d::Vector<TerrainCell*>   m_TerrainCellList;
    cocos2d::Vector<TerrainCell*>   m_TerrainCellCacheList;
    cocos2d::ValueVector            m_TerrainTemplateCellList;
    cocos2d::extension::ScrollView* m_pScrollView;
    cocos2d::DrawNode*              m_pDrawNode;
    cocos2d::Vec2                   m_Offset;
    float                           m_fRadius;
    int                             m_nRows;
    int                             m_nColumns;
    TerrainCell::CELL_TYPE          m_CurrentCellType;
    int                             m_nGeneration;
    int                             m_nLifeNum;
    float                           m_fMinUpdateDelta;
    float                           m_fMaxUpdateDelta;
    float                           m_fCurUpdateDelta;
    
    bool                            m_bEnableAddTerrainCell;
    cocos2d::EventListenerTouchOneByOne* m_pTouchListener;
    std::vector<std::string>        m_vecTemplatesName;
    cocos2d::ValueMap               m_dictTemplates;
    cocos2d::ValueMap               m_dictlevel;
    cocos2d::Vec2                   m_lastTouchDownPos;
};

#endif /* defined(__CCGF__TerrainMgr__) */
