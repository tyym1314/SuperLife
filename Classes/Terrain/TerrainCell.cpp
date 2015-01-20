//
//  TerrainCell.cpp
//  CCGF
//
//  Created by haibo.wang on 14-3-27.
//
//

#include "TerrainCell.h"

USING_NS_CC;
//构造
TerrainCell::TerrainCell(int index_x, int index_y, float posx, float posy, float radius, const::cocos2d::Color4F& color, CELL_TYPE cell_type)
: m_bLevelCell(false)
{
    m_nIndexX           = index_x;     ///X索引
    m_nIndexY           = index_y;     ///Y索引
    m_fPosX             = posx;        ///X坐标
    m_fPosY             = posy;        ///Y坐标
    m_fRadius           = radius;      ///半径
    m_Color             = color;       ///颜色
    m_CellType          = cell_type;   ///地形单元类型
}
//析构
TerrainCell::~TerrainCell()
{
}
//获取x索引
int TerrainCell::getIndexX() const
{
    return m_nIndexX;
}
//设置x索引
void TerrainCell::setIndexX(int indexX)
{
    m_nIndexX = indexX;
}
//获取y索引
int TerrainCell::getIndexY() const
{
    return m_nIndexY;
}
//设置y索引
void TerrainCell::setIndexY(int indexY)
{
    m_nIndexY = indexY;
}
//获取x坐标
float TerrainCell::getPosX() const
{
    return m_fPosX;
}
//设置x坐标
void TerrainCell::setPosX(int posX)
{
    m_fPosX = posX;
}
//获取y坐标
float TerrainCell::getPosY() const
{
    return m_fPosY;
}
//设置y坐标
void TerrainCell::setPosY(int posY)
{
    m_fPosY = posY;
}
//获取半径
float TerrainCell::getRadius() const
{
    return m_fRadius;
}
//设置半径
void TerrainCell::setRadius(float radius)
{
    m_fRadius = radius;
}
//获取地形单元颜色
const::cocos2d::Color4F& TerrainCell::getColor() const
{
    return m_Color;
}
//设置地表单元颜色
void TerrainCell::setColor(const cocos2d::Color4F& color)
{
    m_Color = color;
}
//获取地形单元类型
TerrainCell::CELL_TYPE TerrainCell::getCellType() const
{
    return m_CellType;
}
//设置地形单元类型
void TerrainCell::setCellType(TerrainCell::CELL_TYPE type)
{
    m_CellType = type;
}
//是否为任务模式下的单元
bool TerrainCell::isLevelCell() const
{
    return m_bLevelCell;
}
//设置为任务模式下的单元
void TerrainCell::setLevelCell(bool levelCell)
{
    m_bLevelCell = levelCell;
}