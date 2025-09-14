"use strict";
var __awaiter = (this && this.__awaiter) || function (thisArg, _arguments, P, generator) {
    return new (P || (P = Promise))(function (resolve, reject) {
        function fulfilled(value) { try { step(generator.next(value)); } catch (e) { reject(e); } }
        function rejected(value) { try { step(generator["throw"](value)); } catch (e) { reject(e); } }
        function step(result) { result.done ? resolve(result.value) : new P(function (resolve) { resolve(result.value); }).then(fulfilled, rejected); }
        step((generator = generator.apply(thisArg, _arguments || [])).next());
    });
};
Object.defineProperty(exports, "__esModule", { value: true });
const FileSystem = require("fs");
const XML2JS = require("xml2js");
const Crypto = require("crypto");
/// <reference path="../../index.d.ts" />
const THREE = require("three");
const gameconst_1 = require("../module/gameconst");
class Utils {
    static readConfig(name, ext = '.conf') {
        let conFile = FileSystem.readFileSync(`./conf/${name}${ext}`, 'utf8');
        if (conFile == null) {
            return null;
        }
        return JSON.parse(conFile);
    }
    static reverseMap(mapData) {
        let reverseData = new Map();
        mapData.forEach((value, key) => {
            reverseData.set(value, key);
        }, this);
        return reverseData;
    }
    ;
    static getJSObject(file) {
        return __awaiter(this, void 0, void 0, function* () {
            let xmlData = FileSystem.readFileSync(file, "utf-8");
            return new Promise((resolve, reject) => {
                XML2JS.parseString(xmlData, (err, jsonData) => {
                    if (err) {
                        return reject(err);
                    }
                    else {
                        return resolve(jsonData);
                    }
                });
            });
        });
    }
    static checkNumber(strObj) {
        return !isNaN(Number(strObj));
    }
    static readDir(filepath, extName = 'xml', fileList = null) {
        let pa = FileSystem.readdirSync(filepath);
        if (fileList == null) {
            fileList = new Array();
        }
        pa.forEach((element, index) => {
            let info = FileSystem.statSync(`${filepath}/${element}`);
            if (info.isDirectory()) {
                this.readDir(`${filepath}/${element}`, extName, fileList);
            }
            else {
                if (element.toLowerCase().endsWith(extName)) {
                    fileList.push(`${filepath}/${element}`);
                }
            }
        });
        return fileList;
    }
    static randNumber(min, max) {
        return Math.floor((max - min) * Math.random() + min + 0.5);
    }
    static md5(data) {
        let md5Generate = Crypto.createHash("md5");
        md5Generate.update(data);
        return md5Generate.digest('hex');
    }
    static isZero(vector) {
        if (vector.x == 0 && vector.y == 0 && vector.z == 0) {
            return true;
        }
        return false;
    }
    static ifSphereImpact(s1, s2) {
        return s1.intersectsSphere(s2);
    }
    static ifImpactExt(sphere, aabb) {
        let dist = 0;
        let v = sphere.center.x;
        if (v < aabb.min.x) {
            dist += (aabb.min.x - v) * (aabb.min.x - v);
        }
        if (v > aabb.max.y) {
            dist += (v - aabb.max.y) * (v - aabb.max.y);
        }
        v = sphere.center.z;
        if (v < aabb.min.y)
            dist += (aabb.min.y - v) * (aabb.min.y - v);
        if (v > aabb.max.y)
            dist += (v - aabb.max.y) * (v - aabb.max.y);
        return dist < sphere.radius * sphere.radius;
    }
}
exports.default = Utils;
//# sourceMappingURL=utils.js.map