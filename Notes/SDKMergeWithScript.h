//
//  SDKMergeWithScript.h
//  Notes
//
//  Created by Civet on 2020/7/27.
//  Copyright © 2020 PersonalONBYL. All rights reserved.
//

#ifndef SDKMergeWithScript_h
#define SDKMergeWithScript_h


#endif /* SDKMergeWithScript_h */

/*
 操作步骤:
 选中项目文件->targets->BuildPhases->点击假图标->选择“New Run Java Script”->在Run Script中输入下方合并SDK的脚本代码。
 
 
 if [ "${ACTION}" = "build" ]
 
 then
 
 INSTALL_DIR=${SRCROOT}/Products/${PROJECT_NAME}.framework
 
 DEVICE_DIR=${BUILD_ROOT}/${CONFIGURATION}-iphoneos/${PROJECT_NAME}.framework
 
 SIMULATOR_DIR=${BUILD_ROOT}/${CONFIGURATION}-iphonesimulator/${PROJECT_NAME}.framework
 
 if [ -d "${INSTALL_DIR}" ]
 
 then
 
 rm -rf "${INSTALL_DIR}"
 
 fi
 
 mkdir -p "${INSTALL_DIR}"
 
 cp -R "${DEVICE_DIR}/" "${INSTALL_DIR}/"
 
 #ditto "${DEVICE_DIR}/Headers" "${INSTALL_DIR}/Headers"
 
 lipo -create "${DEVICE_DIR}/${PROJECT_NAME}" "${SIMULATOR_DIR}/${PROJECT_NAME}" -output "${INSTALL_DIR}/${PROJECT_NAME}"
 
 #open "${DEVICE_DIR}"
 
 open "${SRCROOT}/Products"
 
 fi
 

 
 */
