/*****************************************************************************
 *
 * Filename:
 * ---------
 *   camera_sensor_para.h
 *
 * Project:
 * --------
 *   DUMA
 *
 * Description:
 * ------------
 *   Header file of Sensor tuning parameters that should be generated by CCT
 *
 *
 * Author:
 * -------
 *
 *============================================================================
 *             HISTORY
 * Below this line, this part is controlled by CC/CQ. DO NOT MODIFY!!
 *------------------------------------------------------------------------------
 * $Revision:$
 * $Modtime:$
 * $Log:$
 * 
 * 09 12 2012 wcpadmin
 * [ALPS00276400] Remove MTK copyright and legal header on GPL/LGPL related packages
 * .
 *
 * 05 14 2012 hao.wang
 * [ALPS00283632] SP OV8830 Sensor Driver check in
 * .
 *
 * 
 *
 *------------------------------------------------------------------------------
 * Upper this line, this part is controlled by CC/CQ. DO NOT MODIFY!!
 *============================================================================
 ****************************************************************************/
#ifndef _OV8830_CAMERA_SENSOR_PARA_H
#define _OV8830_CAMERA_SENSOR_PARA_H

#define OV8830_CAMERA_SENSOR_REG_DEFAULT_VALUE \
{ \
  {0xFFFFFFFF,0xFFFFFFFF},{0xFFFFFFFF,0xFFFFFFFF},{0xFFFFFFFF,0xFFFFFFFF},{0xFFFFFFFF,0xFFFFFFFF}, \
  {0xFFFFFFFF,0xFFFFFFFF},{0xFFFFFFFF,0xFFFFFFFF},{0xFFFFFFFF,0xFFFFFFFF},{0xFFFFFFFF,0xFFFFFFFF}, \
  {0xFFFFFFFF,0xFFFFFFFF},{0xFFFFFFFF,0xFFFFFFFF},{0xFFFFFFFF,0xFFFFFFFF},{0xFFFFFFFF,0xFFFFFFFF}, \
  {0xFFFFFFFF,0xFFFFFFFF},{0xFFFFFFFF,0xFFFFFFFF},{0xFFFFFFFF,0xFFFFFFFF},{0xFFFFFFFF,0xFFFFFFFF}, \
  {0xFFFFFFFF,0xFFFFFFFF},{0xFFFFFFFF,0xFFFFFFFF},{0xFFFFFFFF,0xFFFFFFFF},{0xFFFFFFFF,0xFFFFFFFF}, \
  {0xFFFFFFFF,0xFFFFFFFF},{0xFFFFFFFF,0xFFFFFFFF},{0xFFFFFFFF,0xFFFFFFFF},{0xFFFFFFFF,0xFFFFFFFF}, \
  {0xFFFFFFFF,0xFFFFFFFF},{0xFFFFFFFF,0xFFFFFFFF},{0xFFFFFFFF,0xFFFFFFFF},{0xFFFFFFFF,0xFFFFFFFF}, \
  {0xFFFFFFFF,0xFFFFFFFF},{0xFFFFFFFF,0xFFFFFFFF},{0xFFFFFFFF,0xFFFFFFFF},{0xFFFFFFFF,0xFFFFFFFF}, \
  {0xFFFFFFFF,0xFFFFFFFF},{0xFFFFFFFF,0xFFFFFFFF},{0xFFFFFFFF,0xFFFFFFFF},{0xFFFFFFFF,0xFFFFFFFF}, \
  {0xFFFFFFFF,0xFFFFFFFF},{0xFFFFFFFF,0xFFFFFFFF},{0xFFFFFFFF,0xFFFFFFFF},{0xFFFFFFFF,ISP_DRIVING_6MA}, \
}

#define OV8830_CAMERA_SENSOR_CCT_DEFAULT_VALUE \
{ \
  {0xFFFFFFFF,0x40},{0xFFFFFFFF,0x40},{0xFFFFFFFF,0x40},{0xFFFFFFFF,0x40},{0xFFFFFFFF,0x40}, \
}

#endif /* __CAMERA_SENSOR_PARA_H */
/* SENSOR FULL SIZE */
