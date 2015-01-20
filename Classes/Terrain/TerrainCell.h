//
//  TerrainCell.h
//  CCGF
//
//  Created by haibo.wang on 14-3-27.
//
//

#ifndef __CCGF__TerrainCell__
#define __CCGF__TerrainCell__

#include "cocos2d.h"
class TerrainCell : public cocos2d::Ref
{
public:
    enum CELL_TYPE {
        RECTANGLE           = 0,                ///矩形
        HEXAGON             = 1,                ///正六边形
        UNKNOWN             = 2                 ///未知
    };
    //构造
    TerrainCell(int index_x, int index_y, float posx, float posy, float radius, const::cocos2d::Color4F& color, CELL_TYPE cell_type);
    //析构
    ~TerrainCell();
    //获取x索引
    int getIndexX() const;
    //设置x索引
    void setIndexX(int indexX);
    //获取y索引
    int getIndexY() const;
    //设置y索引
    void setIndexY(int indexY);
    //获取x坐标
    float getPosX() const;
    //设置x坐标
    void setPosX(int posX);
    //获取y坐标
    float getPosY() const;
    //设置y坐标
    void setPosY(int posY);
    //获取半径
    float getRadius() const;
    //设置半径
    void setRadius(float radius);
    //获取地形单元颜色
    const cocos2d::Color4F& getColor() const;
    //设置地表单元颜色
    void setColor(const cocos2d::Color4F& color);
    //获取地形单元类型
    CELL_TYPE getCellType() const;
    //设置地形单元类型
    void setCellType(CELL_TYPE type);
    //是否为任务模式下的单元
    bool isLevelCell() const;
    //设置为任务模式下的单元
    void setLevelCell(bool levelCell);
private:
    int                 m_nIndexX;                      ///X索引
    int                 m_nIndexY;                      ///Y做引
    float               m_fPosX;                        ///X坐标
    float               m_fPosY;                        ///Y坐标
    float               m_fRadius;                      ///半径
    cocos2d::Color4F    m_Color;                        ///颜色
    CELL_TYPE           m_CellType;                     ///地形单元类型
    bool                m_bLevelCell;                   ///是否为任务模式下的单元
};

#endif /* defined(__CCGF__TerrainCell__) */
