/********************************************************************************
*																				*
*					GSocket：完成端口通讯模块（IOCP Socket）					*
*								——GTcpClient									*
*																				*
*				Copyright © 2009  代码客（卢益贵）  版权所有					*
*						未经许可，不得用于任何项目开发							*
*  QQ:48092788  E-Mail:gcode@qq.com  源码博客：http://blog.csdn.net/guestcode	*
*																				*
*					GSN:34674B4D-1F63-11D3-B64C-11C04F79498E					*
********************************************************************************/

#pragma once

extern BOOL bGTcpCltIsActive;

void GTcpClt_CloseClients(void);
void GTcpClt_FreeClients(void);
void GTcpClt_EndThread(void);

void GTcpClt_Create(void);
void GTcpClt_Destroy(void);
