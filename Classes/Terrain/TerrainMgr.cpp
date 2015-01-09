//
//  TerrainMgr.cpp
//  CCGF
//
//  Created by haibo.wang on 14-3-27.
//
//

#include "TerrainMgr.h"
#include "SceneFactory.h"
#include "SceneConst.h"
#include "GameConst.h"
USING_NS_CC;

TerrainMgr* g_pTerrainMgrInstance = nullptr;
// 单体
TerrainMgr* TerrainMgr::getInstance()
{
    if( g_pTerrainMgrInstance == nullptr )
        g_pTerrainMgrInstance = new TerrainMgr();
    
    return g_pTerrainMgrInstance;
}
// 构造函数
TerrainMgr::TerrainMgr()
    :m_Offset(Vec2::ZERO), m_nRows(0), m_nColumns(0),m_nGeneration(0),m_nLifeNum(0),
    m_CurrentCellType(TerrainCell::UNKNOWN),m_fMinUpdateDelta(0.02f),m_fMaxUpdateDelta(0.5f),
    m_fCurUpdateDelta(0.05f),m_pTouchListener(nullptr)
{
    m_pDrawNode = DrawNode::create();
    m_pDrawNode->retain();
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    m_pTouchListener = EventListenerTouchOneByOne::create();
    m_pTouchListener->setSwallowTouches(true);
    m_pTouchListener->onTouchBegan = CC_CALLBACK_2(TerrainMgr::onTouchBegan, this);
    m_pTouchListener->onTouchMoved = CC_CALLBACK_2(TerrainMgr::onTouchMoved, this);
    m_pTouchListener->onTouchEnded = CC_CALLBACK_2(TerrainMgr::onTouchEnded, this);
    m_pTouchListener->onTouchCancelled = CC_CALLBACK_2(TerrainMgr::onTouchCancelled, this);
    dispatcher->addEventListenerWithSceneGraphPriority(m_pTouchListener, m_pDrawNode);
    loadTemplates();
}
// 析构函数
TerrainMgr::~TerrainMgr()
{
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->removeEventListener(m_pTouchListener);
    CC_SAFE_RELEASE(m_pTouchListener);
}
// 添加地面
void TerrainMgr::addTerrain(TerrainCell::CELL_TYPE cell_type, int rows, int columns, float radius, const cocos2d::Vec2& offset)
{
    m_Offset = offset;
    m_nRows = rows;
    m_nColumns = columns;
    m_CurrentCellType = cell_type;
    if(cell_type == TerrainCell::RECTANGLE)
    {
        BaseScene* runningScene = SceneFactory::getInstance()->getCurrentScene();
        Layer* layer = runningScene->getLayer("TerrainLayer");
        if(runningScene && layer)
            layer->addChild(m_pDrawNode);
        m_pDrawNode->setPosition(offset);
        m_pDrawNode->setContentSize(Size(rows*radius*cos(M_PI_4)*2, columns*radius*cos(M_PI_4)*2));
        Color3B color = SceneFactory::getInstance()->getSceneColor();
        for (int i = 0; i<rows; i++) {
            for (int j = 0; j<columns; j++) {
                TerrainCell* cell = new TerrainCell( i, j, i*radius*cos(M_PI_4)*2, j*radius*cos(M_PI_4)*2, radius, Color4F(Color4B(color.r, color.g, color.b, 100)), cell_type);
                m_TerrainCellList.pushBack(cell);
                
                int vertexNum = 4;
                Vec2 points[] = { Vec2(radius*cos(2*M_PI/vertexNum*0 + M_PI_4) + j*radius*cos(M_PI_4)*2,radius*sin(2*M_PI/vertexNum*0 + M_PI_4) + i*radius*cos(M_PI_4)*2),
                                     Vec2(radius*cos(2*M_PI/vertexNum*1 + M_PI_4) + j*radius*cos(M_PI_4)*2,radius*sin(2*M_PI/vertexNum*1 + M_PI_4) + i*radius*cos(M_PI_4)*2),
                                     Vec2(radius*cos(2*M_PI/vertexNum*2 + M_PI_4) + j*radius*cos(M_PI_4)*2,radius*sin(2*M_PI/vertexNum*2 + M_PI_4) + i*radius*cos(M_PI_4)*2),
                                     Vec2(radius*cos(2*M_PI/vertexNum*3 + M_PI_4) + j*radius*cos(M_PI_4)*2,radius*sin(2*M_PI/vertexNum*3 + M_PI_4) + i*radius*cos(M_PI_4)*2) };
                
                m_pDrawNode->drawPolygon(points, sizeof(points)/sizeof(points[0]), cell->getColor(), 0.5f, Color4F(0.0f,0.0f,0.0f,1.0f));
            }
        }
    }
    else if(cell_type == TerrainCell::HEXAGON)
    {
        BaseScene* runningScene = static_cast<BaseScene*>(Director::getInstance()->getRunningScene());
        Layer* layer = runningScene->getLayer("TerrainLayer");
        if(runningScene && layer)
            layer->addChild(m_pDrawNode);
        m_pDrawNode->setPosition(offset);
        Color3B color = SceneFactory::getInstance()->getSceneColor();
        for (int i = 0; i<rows; i++) {
            for (int j = 0; j<columns; j++) {
                TerrainCell* cell = new TerrainCell( i, j, i*radius, j*radius, radius, Color4F(Color4B(color.r, color.g, color.b, 100)), cell_type);
                m_TerrainCellList.pushBack(cell);
                cell->autorelease();
                
                int vertexNum = 6;
                if(i%2 == 0)
                {
                    Vec2 points[] = { Vec2(radius*cos(2*M_PI/vertexNum*0 + M_PI_2) + j*radius*cos(M_PI_2/3.0f)*2, radius*sin(2*M_PI/vertexNum*0 + M_PI_2) + i*radius*1.5f),
                                         Vec2(radius*cos(2*M_PI/vertexNum*1 + M_PI_2) + j*radius*cos(M_PI_2/3.0f)*2, radius*sin(2*M_PI/vertexNum*1 + M_PI_2) + i*radius*1.5f),
                                         Vec2(radius*cos(2*M_PI/vertexNum*2 + M_PI_2) + j*radius*cos(M_PI_2/3.0f)*2, radius*sin(2*M_PI/vertexNum*2 + M_PI_2) + i*radius*1.5f),
                                         Vec2(radius*cos(2*M_PI/vertexNum*3 + M_PI_2) + j*radius*cos(M_PI_2/3.0f)*2, radius*sin(2*M_PI/vertexNum*3 + M_PI_2) + i*radius*1.5f),
                                         Vec2(radius*cos(2*M_PI/vertexNum*4 + M_PI_2) + j*radius*cos(M_PI_2/3.0f)*2, radius*sin(2*M_PI/vertexNum*4 + M_PI_2) + i*radius*1.5f),
                                         Vec2(radius*cos(2*M_PI/vertexNum*5 + M_PI_2) + j*radius*cos(M_PI_2/3.0f)*2, radius*sin(2*M_PI/vertexNum*5 + M_PI_2) + i*radius*1.5f) };
                    m_pDrawNode->drawPolygon(points, sizeof(points)/sizeof(points[0]), cell->getColor(), 0.5f, Color4F(0.5f,1.0f,0.0f,1.0f));
                }
                else
                {
                    Vec2 points[] = { Vec2(radius*cos(2*M_PI/vertexNum*0 + M_PI_2) + (j+0.5f)*radius*cos(M_PI_2/3.0f)*2, radius*sin(2*M_PI/vertexNum*0 + M_PI_2) + i*radius*1.5f),
                                         Vec2(radius*cos(2*M_PI/vertexNum*1 + M_PI_2) + (j+0.5f)*radius*cos(M_PI_2/3.0f)*2, radius*sin(2*M_PI/vertexNum*1 + M_PI_2) + i*radius*1.5f),
                                         Vec2(radius*cos(2*M_PI/vertexNum*2 + M_PI_2) + (j+0.5f)*radius*cos(M_PI_2/3.0f)*2, radius*sin(2*M_PI/vertexNum*2 + M_PI_2) + i*radius*1.5f),
                                         Vec2(radius*cos(2*M_PI/vertexNum*3 + M_PI_2) + (j+0.5f)*radius*cos(M_PI_2/3.0f)*2, radius*sin(2*M_PI/vertexNum*3 + M_PI_2) + i*radius*1.5f),
                                         Vec2(radius*cos(2*M_PI/vertexNum*4 + M_PI_2) + (j+0.5f)*radius*cos(M_PI_2/3.0f)*2, radius*sin(2*M_PI/vertexNum*4 + M_PI_2) + i*radius*1.5f),
                                         Vec2(radius*cos(2*M_PI/vertexNum*5 + M_PI_2) + (j+0.5f)*radius*cos(M_PI_2/3.0f)*2, radius*sin(2*M_PI/vertexNum*5 + M_PI_2) + i*radius*1.5f) };
                    m_pDrawNode->drawPolygon(points, sizeof(points)/sizeof(points[0]), cell->getColor(), 0.5f, Color4F(0.5f,1.0f,0.0f,1.0f));
                }
            }
        }
    }
}
// 删除地面
void TerrainMgr::removeTerrain()
{
    BaseScene* runningScene = static_cast<BaseScene*>(Director::getInstance()->getRunningScene());
    Layer* layer = runningScene->getLayer("TerrainLayer");
    if(runningScene && layer)
    {
        m_TerrainCellList.clear();
        m_pDrawNode->clear();
        layer->removeChild(m_pDrawNode);
    }
    m_Offset = Vec2::ZERO;
    m_nRows = 0;
    m_nColumns = 0;
    m_nGeneration = 0;
    m_nLifeNum = 0;
    m_CurrentCellType = TerrainCell::UNKNOWN;
}
//更新地表单元
void TerrainMgr::updateTerrain()
{
    m_pDrawNode->clear();
    if(m_CurrentCellType == TerrainCell::RECTANGLE)
    {
        Color4F color = Color4F(SceneFactory::getInstance()->getSceneColor());
        m_nLifeNum = 0;
        for (int k = 0; k < m_TerrainCellList.size(); k++)
        {
            TerrainCell* cell = m_TerrainCellList.at(k);
            if(cell)
            {
                cell->setColor(Color4F(color.r, color.g, color.b, cell->getColor().a));
                int j = cell->getIndexX();
                int i = cell->getIndexY();
                float radius = cell->getRadius();
                int vertexNum = 4;
                Vec2 points[] = { Vec2(radius*cos(2*M_PI/vertexNum*0 + M_PI_4) + j*radius*cos(M_PI_4)*2,radius*sin(2*M_PI/vertexNum*0 + M_PI_4) + i*radius*cos(M_PI_4)*2),
                    Vec2(radius*cos(2*M_PI/vertexNum*1 + M_PI_4) + j*radius*cos(M_PI_4)*2,radius*sin(2*M_PI/vertexNum*1 + M_PI_4) + i*radius*cos(M_PI_4)*2),
                    Vec2(radius*cos(2*M_PI/vertexNum*2 + M_PI_4) + j*radius*cos(M_PI_4)*2,radius*sin(2*M_PI/vertexNum*2 + M_PI_4) + i*radius*cos(M_PI_4)*2),
                    Vec2(radius*cos(2*M_PI/vertexNum*3 + M_PI_4) + j*radius*cos(M_PI_4)*2,radius*sin(2*M_PI/vertexNum*3 + M_PI_4) + i*radius*cos(M_PI_4)*2) };
                
                m_pDrawNode->drawPolygon(points, sizeof(points)/sizeof(points[0]), cell->getColor(), 0.5f, Color4F(0.0f,0.0f,0.0f,1.0f));
                
                if(cell->getColor() == color)
                    m_nLifeNum++;
            }
        }
    }
    else if(m_CurrentCellType == TerrainCell::HEXAGON)
    {
    }
}
//重置
void TerrainMgr::resetTerrain()
{
    m_nGeneration = 0;
    m_nLifeNum = 0;
    for (int k = 0; k < m_TerrainCellList.size(); k++)
    {
        TerrainCell* cell = m_TerrainCellList.at(k);
        if(cell)
        {
            Color3B color = SceneFactory::getInstance()->getSceneColor();
            cell->setColor(Color4F(Color4B(color.r,color.g,color.b,100)));
        }
    }
    updateTerrain();
}
// 更新处理
void TerrainMgr::update(float delta)
{
    static float time = m_fCurUpdateDelta;
    time -= delta;
    if(time <= 0)
    {
        m_nLifeNum = 0;
        Color3B color = SceneFactory::getInstance()->getSceneColor();
        Vector<TerrainCell*> newTerrainCellList;
        for (int k = 0; k < m_TerrainCellList.size(); k++)
        {
            TerrainCell* cell = m_TerrainCellList.at(k);
            TerrainCell* newCell = new TerrainCell(cell->getIndexX(), cell->getIndexY(), cell->getPosX(), cell->    getPosY(), cell->getRadius(),Color4F(Color4B(color.r, color.g, color.b, 100)),cell->getCellType());
            newCell->autorelease();
            if(cell && newCell)
            {
                switch (getLifeNeighborCount(cell)) {
                    case 2:
                        newCell->setColor(cell->getColor());
                        break;
                    case 3:
                        newCell->setColor(Color4F(color));
                        break;
                    default:
                        newCell->setColor(Color4F(Color4B(color.r,color.g,color.b,100)));
                        break;
                }
                if(newCell->getColor() == Color4F(color))
                    m_nLifeNum++;
                newTerrainCellList.pushBack(newCell);
            }
        }
        m_TerrainCellList.clear();
        m_TerrainCellList = newTerrainCellList;
        newTerrainCellList.clear();
        updateTerrain();
        m_nGeneration++;
        if(m_nLifeNum == 0)
            m_nGeneration = 0;
        time = m_fCurUpdateDelta;
    }
}
//获取地表单元相邻邻居节点个数
int TerrainMgr::getLifeNeighborCount(TerrainCell* cell)
{
    int count = 0;
    if(cell != nullptr)
    {
        if(m_CurrentCellType == TerrainCell::RECTANGLE)
        {
            Color3B color = SceneFactory::getInstance()->getSceneColor();
            for (int i = cell->getIndexX()-1; i <= cell->getIndexX()+1; ++i) {
                for (int j = cell->getIndexY()-1; j <= cell->getIndexY()+1; ++j) {
                    if(i == cell->getIndexX() && j == cell->getIndexY())
                        continue;
                    if( i<0 || i>=m_nRows || j<0 || j >= m_nColumns)
                        continue;
                    else
                    {
                        int index = i*m_nRows + j;
                        TerrainCell* neighborCell = m_TerrainCellList.at(index);
                        if(neighborCell->getColor() == Color4F(color))
                            count++;
                    }
                }
            }
        }
    }
    return count;
}
//获取生命对象代数
int TerrainMgr::getGeneration() const
{
    return m_nGeneration;
}
//获取生命对象个数
int TerrainMgr::getLifeNum() const
{
    return  m_nLifeNum;
}
//获取最小更新频率
float TerrainMgr::getMinUpdateDelta() const
{
    return m_fMinUpdateDelta;
}
//获取最大更新频率
float TerrainMgr::getMaxUpdateDelta() const
{
    return m_fMaxUpdateDelta;
}
//获取当前更新频率
float TerrainMgr::getCurUpdateDelta() const
{
    return m_fCurUpdateDelta;
}
//设置当前更新频率
void TerrainMgr::setCurUpdateDelta(float curUpdateDelta)
{
    m_fCurUpdateDelta = curUpdateDelta;
}
// 处理输入
bool TerrainMgr::onTouchBegan(Touch *touch, Event *unused_event)
{
    BaseScene* curScene = SceneFactory::getInstance()->getCurrentScene();
    if(!curScene->IsPaused())
        return true;
    bool dirty = false;
    DrawNode* touchNode = static_cast<DrawNode*>(unused_event->getCurrentTarget());
    if(touchNode)
    {
        Vec2 locationInNode = touchNode->convertToNodeSpace(touch->getLocation());
        for (int i = 0; i < m_TerrainCellList.size(); i++)
        {
            TerrainCell* cell = m_TerrainCellList.at(i);
            if(cell && cell->getCellType() == TerrainCell::RECTANGLE)
            {
                float radius = cell->getRadius();
                Rect rect = Rect(cell->getPosX()-radius*cos(M_PI_4),cell->getPosY()-radius*cos(M_PI_4),radius*cos(M_PI_4)*2,radius*cos(M_PI_4)*2);
                if(rect.containsPoint(locationInNode))
                {
                    Color3B color = SceneFactory::getInstance()->getSceneColor();
                    cell->setColor(Color4F(color));
                    dirty = true;
                    break;
                }
            }
        }
    }
    if(dirty)
        updateTerrain();
    return true;
}
void TerrainMgr::onTouchMoved(Touch *touch, Event *unused_event)
{
    BaseScene* curScene = SceneFactory::getInstance()->getCurrentScene();
    if(!curScene->IsPaused())
        return;
    bool dirty = false;
    DrawNode* touchNode = static_cast<DrawNode*>(unused_event->getCurrentTarget());
    if(touchNode)
    {
        Vec2 locationInNode = touchNode->convertToNodeSpace(touch->getLocation());
        for (int i = 0; i < m_TerrainCellList.size(); i++)
        {
            TerrainCell* cell = m_TerrainCellList.at(i);
            if(cell && cell->getCellType() == TerrainCell::RECTANGLE)
            {
                float radius = cell->getRadius();
                Rect rect = Rect(cell->getPosX()-radius*cos(M_PI_4),cell->getPosY()-radius*cos(M_PI_4),radius*cos(M_PI_4)*2,radius*cos(M_PI_4)*2);
                if(rect.containsPoint(locationInNode))
                {
                    Color3B color = SceneFactory::getInstance()->getSceneColor();
                    cell->setColor(Color4F(color));
                    dirty = true;
                    break;
                }
            }
        }
    }
    if(dirty)
        updateTerrain();

}
void TerrainMgr::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
}
void TerrainMgr::onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
}
//加载模版
void TerrainMgr::loadTemplates()
{
    m_dictTemplates = FileUtils::getInstance()->getValueMapFromFile("templates.plist");
    ValueMap::iterator iter;
    for(iter = m_dictTemplates.begin();iter != m_dictTemplates.end(); iter++)
    {
        m_vecTemplatesName.push_back(iter->first);
    }
}
//加载模版
std::string TerrainMgr::getTemplateName(ssize_t index)
{
    return m_vecTemplatesName[index];
}
//保存模版
void TerrainMgr::saveTemplate(const std::string& name)
{
    ValueVector temp;
    for (int k = 0; k < m_TerrainCellList.size(); k++)
    {
        TerrainCell* cell = m_TerrainCellList.at(k);
        if(cell)
        {
            Color4F sceneColor = Color4F(Color4B(SceneFactory::getInstance()->getSceneColor()));
            if(sceneColor == cell->getColor())
                temp.push_back(Value(1));
            else
                temp.push_back(Value(0));
        }
    }
    m_dictTemplates[name] = temp;
    
    if(std::find(m_vecTemplatesName.begin(), m_vecTemplatesName.end(), name) == m_vecTemplatesName.end())
        m_vecTemplatesName.push_back(name);
    std::string fullpath = FileUtils::getInstance()->getWritablePath() + "/templates/templates.plist";
    FileUtils::getInstance()->writeToFile(m_dictTemplates, fullpath);
}
//获取模版数量
ssize_t TerrainMgr::getTemplateCount()
{
    return m_vecTemplatesName.size();
}