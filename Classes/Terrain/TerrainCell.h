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
    //获取y索引
    int getIndexY() const;
    //获取x坐标
    float getPosX() const;
    //获取y坐标
    float getPosY() const;
    //获取半径
    float getRadius() const;
    //获取地形单元颜色
    const::cocos2d::Color4F& getColor() const;
    //设置地表单元颜色
    void setColor(const cocos2d::Color4F& color);
    //获取地形单元类型
    CELL_TYPE getCellType() const;
private:
    int                 m_nIndexX;                      ///X索引
    int                 m_nIndexY;                      ///Y做引
    float               m_fPosX;                        ///X坐标
    float               m_fPosY;                        ///Y坐标
    float               m_fRadius;                      ///半径
    cocos2d::Color4F    m_Color;                        ///颜色
    CELL_TYPE           m_CellType;                     ///地形单元类型
};

#endif /* defined(__CCGF__TerrainCell__) */
