#ifndef REALTIMEBUTTERFLYPLOT_H
#define REALTIMEBUTTERFLYPLOT_H

//*************************************************************************************************************
//=============================================================================================================
// INCLUDES
//=============================================================================================================

#include "../xdisp_global.h"

#include "realtimeevokedmodel.h"


//*************************************************************************************************************
//=============================================================================================================
// QT INCLUDES
//=============================================================================================================

#include <QWidget>
#include <QPolygonF>
#include <QColor>
#include <QSharedPointer>


//*************************************************************************************************************
//=============================================================================================================
// DEFINE NAMESPACE XDISPLIB
//=============================================================================================================

namespace XDISPLIB
{

struct Modality;


class XDISPSHARED_EXPORT RealTimeButterflyPlot : public QWidget
{
    Q_OBJECT

public:
    typedef QSharedPointer<RealTimeButterflyPlot> SPtr;              /**< Shared pointer type for RealTimeButterflyPlot. */
    typedef QSharedPointer<const RealTimeButterflyPlot> ConstSPtr;   /**< Const shared pointer type for RealTimeButterflyPlot. */

    explicit RealTimeButterflyPlot(QWidget *parent = 0);

    inline void setModel(RealTimeEvokedModel* model);

    void dataUpdate(const QModelIndex& topLeft, const QModelIndex& bottomRight, const QVector<int>& roles = QVector<int>());

    void setSettings(const QList< Modality >& p_qListModalities);

    void setSelectedChannels(const QList<int> &selectedChannels);

    void updateView();

    void setBackgroundColor(const QColor& backgroundColor);

    const QColor& getBackgroundColor();

protected:
    //=========================================================================================================
    /**
    * Is called to paint the incoming real-time data block.
    * Function is painting the real-time butterfly plot
    *
    * @param [in] event pointer to PaintEvent -> not used.
    */
    virtual void paintEvent(QPaintEvent* paintEvent );

private:
    //=========================================================================================================
    /**
    * createPlotPath creates the QPointer path for the data plot.
    *
    * @param[in] index QModelIndex for accessing associated data and model object.
    * @param[in,out] path The QPointerPath to create for the data plot.
    */
    void createPlotPath(qint32 row, QPainterPath& path) const;

    bool                    m_bShowMAG;                         /**< Show Magnetometers channels */
    bool                    m_bShowGRAD;                        /**< Show Gradiometers channels */
    bool                    m_bShowEEG;                         /**< Show EEG channels */
    bool                    m_bShowEOG;                         /**< Show EEG channels */
    bool                    m_bShowMISC;                        /**< Show Miscellaneous channels */
    bool                    m_bIsInit;

    float                   m_fMaxMAG;                          /**< Scale for Magnetometers channels */
    float                   m_fMaxGRAD;                         /**< Scale for Gradiometers channels */
    float                   m_fMaxEEG;                          /**< Scale for EEG channels */
    float                   m_fMaxEOG;                          /**< Scale for EEG channels */
    float                   m_fMaxMISC;                         /**< Scale for Miscellaneous channels */

    RealTimeEvokedModel*    m_pRealTimeEvokedModel;

    qint32                  m_iNumChannels;

    QColor                  m_colCurrentBackgroundColor;

    QList<int>              m_lSelectedChannels;
};


//*************************************************************************************************************
//=============================================================================================================
// INLINE DEFINITIONS
//=============================================================================================================

inline void RealTimeButterflyPlot::setModel(RealTimeEvokedModel* model)
{
    m_pRealTimeEvokedModel = model;

    connect(m_pRealTimeEvokedModel, &RealTimeEvokedModel::dataChanged, this, &RealTimeButterflyPlot::dataUpdate);
}

} // NAMESPACE

#endif // REALTIMEBUTTERFLYPLOT_H
