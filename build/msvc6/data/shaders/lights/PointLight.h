/************************************************************************** *
 *  This file is part of the Coin 3D visualization library.
 *  Copyright (C) 1998-2007 by Systems in Motion.  All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  ("GPL") version 2 as published by the Free Software Foundation.
 *  See the file LICENSE.GPL at the root directory of this source
 *  distribution for additional information about the GNU GPL.
 *
 *  For using Coin with software that can not be combined with the GNU
 *  GPL, and for taking advantage of the additional benefits of our
 *  support services, please contact Systems in Motion about acquiring
 *  a Coin Professional Edition License.
 *
 *  See http://www.coin3d.org/ for more information.
 *
 *  Systems in Motion, Postboks 1283, Pirsenteret, 7462 Trondheim, NORWAY.
 *  http://www.sim.no/  sales@sim.no  coin-support@coin3d.org
 *
\**************************************************************************/

#ifndef COIN_INTERNAL
#error this is a private header file
#endif /* !COIN_INTERNAL */

#ifndef SO_POINTLIGHT_GLSL_H
#define SO_POINTLIGHT_GLSL_H

static const char POINTLIGHT_shadersource[] =
  "\n"
  "void PointLight(in int i,\n"
  "                in vec3 eye,\n"
  "                in vec3 ecPosition3,\n"
  "                in vec3 normal,\n"
  "                inout vec4 ambient,\n"
  "                inout vec4 diffuse,\n"
  "                inout vec4 specular)\n"
  "{\n"
  "  float nDotVP;\n"
  "  float nDotHV;\n"
  "  float pf;  \n"
  "  float att;\n"
  "  float d;          \n"
  "  vec3 VP;\n"
  "  vec3 halfvec;\n"
  "\n"
  "  VP = vec3(gl_LightSource[i].position) - ecPosition3;\n"
  "  d = length(VP);\n"
  "  \n"
  "  VP = normalize(VP);\n"
  "  \n"
  "  att = 1.0 / (gl_LightSource[i].constantAttenuation +\n"
  "               gl_LightSource[i].linearAttenuation * d +\n"
  "               gl_LightSource[i].quadraticAttenuation * d * d);\n"
  "  \n"
  "  halfvec = normalize(VP + eye);\n"
  "  nDotVP = max(0.0, dot(normal, VP));\n"
  "  nDotHV = max(0.0, dot(normal, halfvec));\n"
  "  \n"
  "  float shininess = gl_FrontMaterial.shininess;\n"
  "\n"
  "  if (nDotVP == 0.0)\n"
  "    pf = 0.0;\n"
  "  else \n"
  "    pf = pow(nDotHV, shininess);\n"
  "  \n"
  "  ambient += gl_LightSource[i].ambient * att;\n"
  "  diffuse += gl_LightSource[i].diffuse * nDotVP * att;\n"
  "  specular += gl_LightSource[i].specular * pf * att;\n"
  "}\n";

#endif /* ! SO_POINTLIGHT_GLSL_H */
