function dv_rolloutManager(handlersDefsArray, baseHandler) {
    this.handle = function () {
        var errorsArr = [];

        var handler = chooseEvaluationHandler(handlersDefsArray);
        if (handler) {
            var errorObj = handleSpecificHandler(handler);
            if (errorObj === null) {
                return errorsArr;
            }
            else {
                var debugInfo = handler.onFailure();
                if (debugInfo) {
                    for (var key in debugInfo) {
                        if (debugInfo.hasOwnProperty(key)) {
                            if (debugInfo[key] !== undefined || debugInfo[key] !== null) {
                                errorObj[key] = encodeURIComponent(debugInfo[key]);
                            }
                        }
                    }
                }
                errorsArr.push(errorObj);
            }
        }

        var errorObjHandler = handleSpecificHandler(baseHandler);
        if (errorObjHandler) {
            errorObjHandler['dvp_isLostImp'] = 1;
            errorsArr.push(errorObjHandler);
        }
        return errorsArr;
    };

    function handleSpecificHandler(handler) {
        var url;
        var errorObj = null;

        try {
            url = handler.createRequest();
            if (url) {
                if (!handler.sendRequest(url)) {
                    errorObj = createAndGetError('sendRequest failed.',
                        url,
                        handler.getVersion(),
                        handler.getVersionParamName(),
                        handler.dv_script);
                }
            } else {
                errorObj = createAndGetError('createRequest failed.',
                    url,
                    handler.getVersion(),
                    handler.getVersionParamName(),
                    handler.dv_script,
                    handler.dvScripts,
                    handler.dvStep,
                    handler.dvOther
                );
            }
        }
        catch (e) {
            errorObj = createAndGetError(e.name + ': ' + e.message, url, handler.getVersion(), handler.getVersionParamName(), (handler ? handler.dv_script : null));
        }

        return errorObj;
    }

    function createAndGetError(error, url, ver, versionParamName, dv_script, dvScripts, dvStep, dvOther) {
        var errorObj = {};
        errorObj[versionParamName] = ver;
        errorObj['dvp_jsErrMsg'] = encodeURIComponent(error);
        if (dv_script && dv_script.parentElement && dv_script.parentElement.tagName && dv_script.parentElement.tagName == 'HEAD') {
            errorObj['dvp_isOnHead'] = '1';
        }
        if (url) {
            errorObj['dvp_jsErrUrl'] = url;
        }
        if (dvScripts) {
            var dvScriptsResult = '';
            for (var id in dvScripts) {
                if (dvScripts[id] && dvScripts[id].src) {
                    dvScriptsResult += encodeURIComponent(dvScripts[id].src) + ":" + dvScripts[id].isContain + ",";
                }
            }
            
           
           
        }
        return errorObj;
    }

    function chooseEvaluationHandler(handlersArray) {
        var config = window._dv_win.dv_config;
        var index = 0;
        var isEvaluationVersionChosen = false;
        if (config.handlerVersionSpecific) {
            for (var i = 0; i < handlersArray.length; i++) {
                if (handlersArray[i].handler.getVersion() == config.handlerVersionSpecific) {
                    isEvaluationVersionChosen = true;
                    index = i;
                    break;
                }
            }
        }
        else if (config.handlerVersionByTimeIntervalMinutes) {
            var date = config.handlerVersionByTimeInputDate || new Date();
            var hour = date.getUTCHours();
            var minutes = date.getUTCMinutes();
            index = Math.floor(((hour * 60) + minutes) / config.handlerVersionByTimeIntervalMinutes) % (handlersArray.length + 1);
            if (index != handlersArray.length) { 
                isEvaluationVersionChosen = true;
            }
        }
        else {
            var rand = config.handlerVersionRandom || (Math.random() * 100);
            for (var i = 0; i < handlersArray.length; i++) {
                if (rand >= handlersArray[i].minRate && rand < handlersArray[i].maxRate) {
                    isEvaluationVersionChosen = true;
                    index = i;
                    break;
                }
            }
        }

        if (isEvaluationVersionChosen == true && handlersArray[index].handler.isApplicable()) {
            return handlersArray[index].handler;
        }
        else {
            return null;
        }
    }    
}

function getCurrentTime() {
    "use strict";
    if (Date.now) {
        return Date.now();
    }
    return (new Date()).getTime();
}

function doesBrowserSupportHTML5Push() {
    "use strict";
    return typeof window.parent.postMessage === 'function' && window.JSON;
}

function dv_GetParam(url, name) {
    name = name.replace(/[\[]/, "\\\[").replace(/[\]]/, "\\\]");
    var regexS = "[\\?&]" + name + "=([^&#]*)";
    var regex = new RegExp(regexS, 'i');
    var results = regex.exec(url);
    if (results == null) {
        return null;
    }
    else {
        return results[1];
    }
}

function dv_GetKeyValue(url) {
    var keyReg = new RegExp(".*=");
    var keyRet = url.match(keyReg)[0];
    keyRet = keyRet.replace("=", "");

    var valReg = new RegExp("=.*");
    var valRet = url.match(valReg)[0];
    valRet = valRet.replace("=", "");

    return {key: keyRet, value: valRet};
}

function dv_Contains(array, obj) {
    var i = array.length;
    while (i--) {
        if (array[i] === obj) {
            return true;
        }
    }
    return false;
}

function dv_GetDynamicParams(url, prefix) {
    try {
        prefix = (prefix != undefined && prefix != null) ? prefix : 'dvp';
        var regex = new RegExp("[\\?&](" + prefix + "_[^&]*=[^&#]*)", "gi");
        var dvParams = regex.exec(url);

        var results = [];
        while (dvParams != null) {
            results.push(dvParams[1]);
            dvParams = regex.exec(url);
        }
        return results;
    }
    catch (e) {
        return [];
    }
}

function dv_createIframe() {
    var iframe;
    if (document.createElement && (iframe = document.createElement('iframe'))) {
        iframe.name = iframe.id = 'iframe_' + Math.floor((Math.random() + "") * 1000000000000);
        iframe.width = 0;
        iframe.height = 0;
        iframe.style.display = 'none';
        iframe.src = 'about:blank';
    }

    return iframe;
}

function dv_GetRnd() {
    return ((new Date()).getTime() + "" + Math.floor(Math.random() * 1000000)).substr(0, 16);
}

function dv_SendErrorImp(serverUrl, errorsArr) {

    for (var j = 0; j < errorsArr.length; j++) {
        var errorObj = errorsArr[j];
        var errorImp = dv_CreateAndGetErrorImp(serverUrl, errorObj);
        dv_sendImgImp(errorImp);
    }
}

function dv_CreateAndGetErrorImp(serverUrl, errorObj) {
    var errorQueryString = '';
    for (var key in errorObj) {
        if (errorObj.hasOwnProperty(key)) {
            if (key.indexOf('dvp_jsErrUrl') == -1) {
                errorQueryString += '&' + key + '=' + errorObj[key];
            } else {
                var params = ['ctx', 'cmp', 'plc', 'sid'];
                for (var i = 0; i < params.length; i++) {
                    var pvalue = dv_GetParam(errorObj[key], params[i]);
                    if (pvalue) {
                        errorQueryString += '&dvp_js' + params[i] + '=' + pvalue;
                    }
                }
            }
        }
    }

    var windowProtocol = 'https:';
    var sslFlag = '&ssl=1';

    var errorImp = windowProtocol + '//' + serverUrl + sslFlag + errorQueryString;
    return errorImp;
}

function dv_sendImgImp(url) {
    (new Image()).src = url;
}

function dv_getPropSafe(obj, propName) {
    try {
        if (obj) {
            return obj[propName];
        }
    } catch (e) {
    }
}

function dvType() {
    var that = this;
    var eventsForDispatch = {};
    this.t2tEventDataZombie = {};

    this.processT2TEvent = function (data, tag) {
        try {
            if (tag.ServerPublicDns) {
                var tpsServerUrl = tag.dv_protocol + '//' + tag.ServerPublicDns + '/event.gif?impid=' + tag.uid;

                if (!tag.uniquePageViewId) {
                    tag.uniquePageViewId = data.uniquePageViewId;
                }

                tpsServerUrl += '&upvid=' + tag.uniquePageViewId;
                $dv.domUtilities.addImage(tpsServerUrl, tag.tagElement.parentElement);
            }
        } catch (e) {
            try {
                dv_SendErrorImp(window._dv_win.dv_config.tpsErrAddress + '/visit.jpg?ctx=818052&cmp=1619415&dvtagver=6.1.src&jsver=0&dvp_ist2tProcess=1', {dvp_jsErrMsg: encodeURIComponent(e)});
            } catch (ex) {
            }
        }
    };

    this.processTagToTagCollision = function (collision, tag) {
        var i;
        for (i = 0; i < collision.eventsToFire.length; i++) {
            this.pubSub.publish(collision.eventsToFire[i], tag.uid);
        }
        var tpsServerUrl = tag.dv_protocol + '//' + tag.ServerPublicDns + '/event.gif?impid=' + tag.uid;
        tpsServerUrl += '&colltid=' + collision.allReasonsForTagBitFlag;

        for (i = 0; i < collision.reasons.length; i++) {
            var reason = collision.reasons[i];
            tpsServerUrl += '&' + reason.name + "ms=" + reason.milliseconds;
        }

        if (collision.thisTag) {
            tpsServerUrl += '&tlts=' + collision.thisTag.t2tLoadTime;
        }
        if (tag.uniquePageViewId) {
            tpsServerUrl += '&upvid=' + tag.uniquePageViewId;
        }
        $dv.domUtilities.addImage(tpsServerUrl, tag.tagElement.parentElement);
    };

    this.processBSIdFound = function (bsID, tag) {
        var tpsServerUrl = tag.dv_protocol + '//' + tag.ServerPublicDns + '/event.gif?impid=' + tag.uid;
        tpsServerUrl += '&bsimpid=' + bsID;
        if (tag.uniquePageViewId) {
            tpsServerUrl += '&upvid=' + tag.uniquePageViewId;
        }
        $dv.domUtilities.addImage(tpsServerUrl, tag.tagElement.parentElement);
    };

    this.processBABSVerbose = function (verboseReportingValues, tag) {
        var queryString = "";
        


        var dvpPrepend = "&dvp_BABS_";
        queryString += dvpPrepend + 'NumBS=' + verboseReportingValues.bsTags.length;

        for (var i = 0; i < verboseReportingValues.bsTags.length; i++) {
            var thisFrame = verboseReportingValues.bsTags[i];

            queryString += dvpPrepend + 'GotCB' + i + '=' + thisFrame.callbackReceived;
            queryString += dvpPrepend + 'Depth' + i + '=' + thisFrame.depth;

            if (thisFrame.callbackReceived) {
                if (thisFrame.bsAdEntityInfo && thisFrame.bsAdEntityInfo.comparisonItems) {
                    for (var itemIndex = 0; itemIndex < thisFrame.bsAdEntityInfo.comparisonItems.length; itemIndex++) {
                        var compItem = thisFrame.bsAdEntityInfo.comparisonItems[itemIndex];
                        queryString += dvpPrepend + "tag" + i + "_" + compItem.name + '=' + compItem.value;
                    }
                }
            }
        }

        if (queryString.length > 0) {
            var tpsServerUrl = '';
            if (tag) {
                var tpsServerUrl = tag.dv_protocol + '//' + tag.ServerPublicDns + '/event.gif?impid=' + tag.uid;
            }
            var requestString = tpsServerUrl + queryString;
            $dv.domUtilities.addImage(requestString, tag.tagElement.parentElement);
        }
    };

    var messageEventListener = function (event) {
        try {
            var timeCalled = getCurrentTime();
            var data = window.JSON.parse(event.data);
            if (!data.action) {
                data = window.JSON.parse(data);
            }
            var myUID;
            var visitJSHasBeenCalledForThisTag = false;
            if ($dv.tags) {
                for (var uid in $dv.tags) {
                    if ($dv.tags.hasOwnProperty(uid) && $dv.tags[uid] && $dv.tags[uid].t2tIframeId === data.iFrameId) {
                        myUID = uid;
                        visitJSHasBeenCalledForThisTag = true;
                        break;
                    }
                }
            }

            var tag;
            switch (data.action) {
                case 'uniquePageViewIdDetermination':
                    if (visitJSHasBeenCalledForThisTag) {
                        $dv.processT2TEvent(data, $dv.tags[myUID]);
                        $dv.t2tEventDataZombie[data.iFrameId] = undefined;
                    }
                    else {
                        data.wasZombie = 1;
                        $dv.t2tEventDataZombie[data.iFrameId] = data;
                    }
                    break;
                case 'maColl':
                    tag = $dv.tags[myUID];
                    if (!tag.uniquePageViewId) {
                        tag.uniquePageViewId = data.uniquePageViewId;
                    }
                    data.collision.commonRecievedTS = timeCalled;
                    $dv.processTagToTagCollision(data.collision, tag);
                    break;
                case 'bsIdFound':
                    tag = $dv.tags[myUID];
                    if (!tag.uniquePageViewId) {
                        tag.uniquePageViewId = data.uniquePageViewId;
                    }
                    $dv.processBSIdFound(data.id, tag);
                    break;
                case 'babsVerbose':
                    try {
                        tag = $dv.tags[myUID];
                        $dv.processBABSVerbose(data, tag);
                    } catch (err) {
                    }
                    break;
            }

        } catch (e) {
            try {
                dv_SendErrorImp(window._dv_win.dv_config.tpsErrAddress + '/visit.jpg?ctx=818052&cmp=1619415&dvtagver=6.1.src&jsver=0&dvp_ist2tListener=1', {dvp_jsErrMsg: encodeURIComponent(e)});
            } catch (ex) {
            }
        }
    };

    if (window.addEventListener) {
        addEventListener("message", messageEventListener, false);
    }
    else {
        attachEvent("onmessage", messageEventListener);
    }

    this.pubSub = (function () {
        var previousEventsCapacity = 1000;
        var subscribers = {};       
        var eventsHistory = {};     
        var prerenderHistory = {};  
        return {
            subscribe: function (eventName, id, actionName, func, errFunc) {
                    handleHistoryEvents(eventName, id, func, errFunc);
                    if (!subscribers[eventName + id]) {
                        subscribers[eventName + id] = [];
                    }
                    subscribers[eventName + id].push({Func: func, ErrFunc: errFunc, ActionName: actionName});
            },

            publish: function (eventName, id, args) {
                var actionsResults = [];
                try {
                    if (eventName && id) {
                        if ($dv && $dv.tags[id] && $dv.tags[id].prndr) {
                            prerenderHistory[id] = prerenderHistory[id] || [];
                            prerenderHistory[id].push({eventName: eventName, args: args});
                        }
                        else {
                            actionsResults.push.apply(actionsResults, publishEvent(eventName, id, args));
                        }
                    }
                } catch (e) {
                }
                return actionsResults.join('&');
            },

            publishHistoryRtnEvent: function (id) {
                var actionsResults = [];
                if (prerenderHistory[id] instanceof Array) {
                    for (var i = 0; i < prerenderHistory[id].length; i++) {
                        var eventName = prerenderHistory[id][i].eventName;
                        var args = prerenderHistory[id][i].args;
                        if (eventName) {
                            actionsResults.push.apply(actionsResults, publishEvent(eventName, id, args));
                        }
                    }
                }

                prerenderHistory[id] = [];

                return actionsResults;
            }
        };

        function publishEvent(eventName, id, args) {
            var actionsResults = [];
            if (!eventsHistory[id]) {
                eventsHistory[id] = [];
            }
            if (eventsHistory[id].length < previousEventsCapacity) {
                eventsHistory[id].push({eventName: eventName, args: args});
            }

            if (subscribers[eventName + id] instanceof Array) {
                for (var i = 0; i < subscribers[eventName + id].length; i++) {
                    var funcObject = subscribers[eventName + id][i];
                    if (funcObject && funcObject.Func && typeof funcObject.Func == "function" && funcObject.ActionName) {
                        var isSucceeded = true;
                        try {
                            funcObject.Func(id, args);
                        } catch (e) {
                            isSucceeded = false;
                            if (typeof funcObject.ErrFunc == "function") {
                                runSafely(function () {
                                    funcObject.ErrFunc(e);
                                });
                            }
                        }
                        actionsResults.push(encodeURIComponent(funcObject.ActionName) + '=' + (isSucceeded ? '1' : '0'));
                    }
                }
            }

            return actionsResults;
        }

        function handleHistoryEvents(eventName, id, func, errFunc) {
            try {
                if (eventsHistory[id] instanceof Array) {
                    for (var i = 0; i < eventsHistory[id].length; i++) {
                        if (eventsHistory[id][i] && eventsHistory[id][i].eventName === eventName) {
                            func(id, eventsHistory[id][i].args);
                        }
                    }
                }
            } catch (e) {
                if (typeof errFunc == "function") {
                    runSafely(function () {
                        errFunc(e);
                    });
                }
            }
        }
    })();

    this.domUtilities = new function () {
        function getDefaultParent() {
            return document.body || document.head || document.documentElement;
        }

        this.createImage = function (parentElement) {
            parentElement = parentElement || getDefaultParent();
            var image = parentElement.ownerDocument.createElement("img");
            image.width = 0;
            image.height = 0;
            image.style.display = 'none';
            image.src = '';
            parentElement.insertBefore(image, parentElement.firstChild);
            return image;
        };

        var imgArr = [];
        var nextImg = 0;
        var imgArrCreated = false;
        if (!navigator.sendBeacon) {
            imgArr[0] = this.createImage();
            imgArr[1] = this.createImage();
            imgArrCreated = true;
        }

        this.addImage = function (url, parentElement, useGET, usePrerenderedImage) {
            parentElement = parentElement || getDefaultParent();
            if (!useGET && navigator.sendBeacon) {
                var message = appendCacheBuster(url);
                navigator.sendBeacon(message, {});
            } else {
                var image;
                if (usePrerenderedImage && imgArrCreated) {
                    image = imgArr[nextImg];
                    image.src = appendCacheBuster(url);
                    nextImg = (nextImg + 1) % imgArr.length;
                } else {
                    image = this.createImage(parentElement);
                    image.src = appendCacheBuster(url);
                    parentElement.insertBefore(image, parentElement.firstChild);
                }
            }
        };


        this.addScriptResource = function (url, parentElement) {
            parentElement = parentElement || getDefaultParent();
            var scriptElem = parentElement.ownerDocument.createElement("script");
            scriptElem.type = 'text/javascript';
            scriptElem.src = appendCacheBuster(url);
            parentElement.insertBefore(scriptElem, parentElement.firstChild);
        };

        this.addScriptCode = function (srcCode, parentElement) {
            parentElement = parentElement || getDefaultParent();
            var scriptElem = parentElement.ownerDocument.createElement("script");
            scriptElem.type = 'text/javascript';
            scriptElem.innerHTML = srcCode;
            parentElement.insertBefore(scriptElem, parentElement.firstChild);
        };

        this.addHtml = function (srcHtml, parentElement) {
            parentElement = parentElement || getDefaultParent();
            var divElem = parentElement.ownerDocument.createElement("div");
            divElem.style = "display: inline";
            divElem.innerHTML = srcHtml;
            parentElement.insertBefore(divElem, parentElement.firstChild);
        };
    };

    this.resolveMacros = function (str, tag) {
        var viewabilityData = tag.getViewabilityData();
        var viewabilityBuckets = viewabilityData && viewabilityData.buckets ? viewabilityData.buckets : {};
        var upperCaseObj = objectsToUpperCase(tag, viewabilityData, viewabilityBuckets);
        var newStr = str.replace('[DV_PROTOCOL]', upperCaseObj.DV_PROTOCOL);
        newStr = newStr.replace('[PROTOCOL]', upperCaseObj.PROTOCOL);
        newStr = newStr.replace(/\[(.*?)\]/g, function (match, p1) {
            var value = upperCaseObj[p1];
            if (value === undefined || value === null) {
                value = '[' + p1 + ']';
            }
            return encodeURIComponent(value);
        });
        return newStr;
    };

    this.settings = new function () {
    };

    this.tagsType = function () {
    };

    this.tagsPrototype = function () {
        this.add = function (tagKey, obj) {
            if (!that.tags[tagKey]) {
                that.tags[tagKey] = new that.tag();
            }
            for (var key in obj) {
                that.tags[tagKey][key] = obj[key];
            }
        };
    };

    this.tagsType.prototype = new this.tagsPrototype();
    this.tagsType.prototype.constructor = this.tags;
    this.tags = new this.tagsType();

    this.tag = function () {
    };

    this.tagPrototype = function () {
        this.set = function (obj) {
            for (var key in obj) {
                this[key] = obj[key];
            }
        };

        this.getViewabilityData = function () {
        };
    };

    this.tag.prototype = new this.tagPrototype();
    this.tag.prototype.constructor = this.tag;

    
    this.eventBus = (function () {
        var getRandomActionName = function () {
            return 'EventBus_' + Math.random().toString(36) + Math.random().toString(36);
        };
        return {
            addEventListener: function (dvFrame, eventName, func, errFunc) {
                that.pubSub.subscribe(eventName, dvFrame.$frmId, getRandomActionName(), func, errFunc);
            },
            dispatchEvent: function (dvFrame, eventName, data) {
                that.pubSub.publish(eventName, dvFrame.$frmId, data);
            }
        };
    })();

    
    var messagesClass = function () {
        var waitingMessages = [];

        this.registerMsg = function (dvFrame, data) {
            if (!waitingMessages[dvFrame.$frmId]) {
                waitingMessages[dvFrame.$frmId] = [];
            }

            waitingMessages[dvFrame.$frmId].push(data);

            if (dvFrame.$uid) {
                sendWaitingEventsForFrame(dvFrame, dvFrame.$uid);
            }
        };

        this.startSendingEvents = function (dvFrame, impID) {
            sendWaitingEventsForFrame(dvFrame, impID);
            
        };

        function sendWaitingEventsForFrame(dvFrame, impID) {
            if (waitingMessages[dvFrame.$frmId]) {
                var eventObject = {};
                while (waitingMessages[dvFrame.$frmId].length) {
                    var obj = waitingMessages[dvFrame.$frmId].shift();
                    for (var key in obj) {
                        if (typeof obj[key] !== 'function' && obj.hasOwnProperty(key)) {
                            eventObject[key] = obj[key];
                        }
                    }
                }
                that.registerEventCall(impID, eventObject);
            }
        }

        function startMessageManager() {
            for (var frm in waitingMessages) {
                if (frm && frm.$uid) {
                    sendWaitingEventsForFrame(frm, frm.$uid);
                }
            }
            setTimeout(startMessageManager, 10);
        }
    };
    this.messages = new messagesClass();

    var MAX_EVENTS_THRESHOLD = 100;
    window.eventsCounter = window.eventsCounter || {};
    var getImpressionIdToCall = function (impressionId) {
        return window.eventsCounter[impressionId] < MAX_EVENTS_THRESHOLD ? impressionId : 'tme-' + impressionId;
    };

    this.registerEventCall = function (impressionId, eventObject, timeoutMs, isRegisterEnabled, usePrerenderedImage) {

        window.eventsCounter[impressionId] =
            window.eventsCounter[impressionId] ? window.eventsCounter[impressionId] + 1 : 1;


        var avoTimeout = 0;
        if (this.tags[impressionId] && this.tags[impressionId].AVO
            && this.tags[impressionId].AVO['cto'] && !isNaN(this.tags[impressionId].AVO['cto'])) {
            avoTimeout = window._dv_win.$dv.tags[impressionId].AVO['cto'];
        }

        if (isRegisterEnabled !== false && avoTimeout) {
            addEventCallForDispatch(impressionId, eventObject);

            if (!timeoutMs || isNaN(timeoutMs)) {
                timeoutMs = avoTimeout;
            }

            var localThat = this;
            setTimeout(
                function () {
                    localThat.dispatchEventCalls(impressionId);
                }, timeoutMs);

        } else {
            this.dispatchEventImmediate(impressionId, eventObject);
        }
    };

    this.dispatchEventImmediate = function (impressionId, eventObject, timeoutMs, isRegisterEnabled, usePrerenderedImage) {
        var url = this.tags[impressionId].protocol + '//' + this.tags[impressionId].ServerPublicDns + "/event.gif?impid=" +impressionId + '&' + createQueryStringParams(eventObject);

        this.domUtilities.addImage(url, this.tags[impressionId].tagElement.parentNode, false, usePrerenderedImage);
    };

    var mraidObjectCache;
    this.getMraid = function () {
        var context = window._dv_win || window;
        var iterationCounter = 0;
        var maxIterations = 20;

        function getMraidRec(context) {
            iterationCounter++;
            var isTopWindow = context.parent == context;
            if (context.mraid || isTopWindow) {
                return context.mraid;
            } else {
                return ( iterationCounter <= maxIterations ) && getMraidRec(context.parent);
            }
        }

        try {
            return mraidObjectCache = mraidObjectCache || getMraidRec(context);
        } catch (e) {
        }
    };

    var dispatchEventCallsNow = function (impressionId, eventObject) {
        addEventCallForDispatch(impressionId, eventObject);
        dispatchEventCalls(impressionId);
    };

    var addEventCallForDispatch = function (impressionId, eventObject) {
        for (var key in eventObject) {
            if (typeof eventObject[key] !== 'function' && eventObject.hasOwnProperty(key)) {
                if (!eventsForDispatch[impressionId]) {
                    eventsForDispatch[impressionId] = {};
                }
                eventsForDispatch[impressionId][key] = eventObject[key];
            }
        }
    };

    this.dispatchRegisteredEventsFromAllTags = function () {
        for (var impressionId in this.tags) {
            if (typeof this.tags[impressionId] !== 'function' && typeof this.tags[impressionId] !== 'undefined') {
                this.dispatchEventCalls(impressionId);
            }
        }

        
        this.registerEventCall = this.dispatchEventImmediate;
    };

    this.dispatchEventCalls = function (impressionId) {
        if (typeof eventsForDispatch[impressionId] !== 'undefined' && eventsForDispatch[impressionId] != null) {
            var url = this.tags[impressionId].protocol + '//' + this.tags[impressionId].ServerPublicDns +
                "/event.gif?impid=" + impressionId+ '&' + createQueryStringParams(eventsForDispatch[impressionId]);
            this.domUtilities.addImage(url, this.tags[impressionId].tagElement.parentElement);
            eventsForDispatch[impressionId] = null;
        }
    };

    if (window.addEventListener) {
        window.addEventListener('unload', function () {
            that.dispatchRegisteredEventsFromAllTags();
        }, false);
        window.addEventListener('beforeunload', function () {
            that.dispatchRegisteredEventsFromAllTags();
        }, false);
    }
    else if (window.attachEvent) {
        window.attachEvent('onunload', function () {
            that.dispatchRegisteredEventsFromAllTags();
        }, false);
        window.attachEvent('onbeforeunload', function () {
            that.dispatchRegisteredEventsFromAllTags();
        }, false);
    }
    else {
        window.document.body.onunload = function () {
            that.dispatchRegisteredEventsFromAllTags();
        };
        window.document.body.onbeforeunload = function () {
            that.dispatchRegisteredEventsFromAllTags();
        };
    }

    var createQueryStringParams = function (values) {
        var params = '';
        for (var key in values) {
            if (typeof values[key] !== 'function') {
                var value = encodeURIComponent(values[key]);
                if (params === '') {
                    params += key + '=' + value;
                }
                else {
                    params += '&' + key + '=' + value;
                }
            }
        }

        return params;
    };

    this.Enums = {
        BrowserId: {Others: 0, IE: 1, Firefox: 2, Chrome: 3, Opera: 4,
            Safari: 5, ChromeWebView: 6, SafariWebView: 7, PhantomJS: 99},
        TrafficScenario: {OnPage: 1, SameDomain: 2, CrossDomain: 128}
    };

    this.CommonData = {};

    var runSafely = function (action) {
        try {
            var ret = action();
            return ret !== undefined ? ret : true;
        } catch (e) {
            return false;
        }
    };

    var objectsToUpperCase = function () {
        var upperCaseObj = {};
        for (var i = 0; i < arguments.length; i++) {
            var obj = arguments[i];
            for (var key in obj) {
                if (obj.hasOwnProperty(key)) {
                    upperCaseObj[key.toUpperCase()] = obj[key];
                }
            }
        }
        return upperCaseObj;
    };

    var appendCacheBuster = function (url) {
        if (url !== undefined && url !== null && url.match("^http") == "http") {
            if (url.indexOf('?') !== -1) {
                if (url.slice(-1) == '&') {
                    url += 'cbust=' + dv_GetRnd();
                }
                else {
                    url += '&cbust=' + dv_GetRnd();
                }
            }
            else {
                url += '?cbust=' + dv_GetRnd();
            }
        }
        return url;
    };
}

var BrowserDetector = function () {
    var DetectionAreaEnum = {
        USER_AGENT_ONLY: 0,
        PROPERTIES_ONLY: 1,
        USER_AGENT_AND_PROPERTIES: 2
    };
    var BrowserTypeEnum = {
        Other: 0,
        IE: 1,
        Firefox: 2,
        Chrome: 3,
        Opera: 4,
        Safari: 5,
        ChromeWebView: 6,
        SafariWebView: 7,
        PhantomJS: 99
    };

    var Browser = function (browserID, detectionArea, browserDetectorRegexStr, browserVersionRegexStr, propertiesRuleFunc) {
        return {
            browserID: browserID,
            version: '',
            detectionArea: detectionArea,
            userAgentRules: {
                browserTypeRegexStr: browserDetectorRegexStr,
                browserVersionRegexStr: browserVersionRegexStr,
                passed: false
            },
            propertiesRules: {
                evaluatePropertiesRule: propertiesRuleFunc,
                passed: false
            }
        }
    };

    
    var BrowsersData = [

        
        Browser(
            BrowserTypeEnum.ChromeWebView,
            DetectionAreaEnum.USER_AGENT_ONLY,
            '(?:wv(.*?))version\/[0-9]+(?:.[0-9]+)* chrome\/[0-9]+(?:.[0-9]+)* mobile|version\/[0-9]+(?:.[0-9]+)* chrome\/[0-9]+(?:.[0-9]+)* mobile', 'chrome\/',
            null),
        Browser(
            BrowserTypeEnum.SafariWebView,
            DetectionAreaEnum.USER_AGENT_AND_PROPERTIES,
            '(?=.*(iphone|ipod|ipad))(?=^(?:(?!safari).)*$).*$', '',
            function () {
                return !window.navigator.standalone;
            }
        ),
        Browser(
            BrowserTypeEnum.IE,
            DetectionAreaEnum.PROPERTIES_ONLY,
            'msie|trident/7.*rv:11|rv:11.*trident/7|edge/', '(msie |rv:| edge/)',
            function () {
                return document.uniqueID != undefined &&
                    typeof document.uniqueID == 'string' &&
                    ((document.documentMode != undefined && document.documentMode >= 0) ||
                    (document.all != undefined && typeof document.all == 'object') ||
                    (window.ActiveXObject != undefined && typeof window.ActiveXObject == "function")) ||
                    (window.document && window.document.updateSettings && typeof window.document.updateSettings == "function");
            }),
        Browser(
            BrowserTypeEnum.Firefox,
            DetectionAreaEnum.PROPERTIES_ONLY,
            'firefox', 'firefox\/',
            function () {
                return window.mozInnerScreenY != undefined &&
                    typeof window.mozInnerScreenY == 'number' &&
                    window.mozPaintCount != undefined &&
                    window.mozPaintCount >= 0 &&
                    window.InstallTrigger != undefined &&
                    window.InstallTrigger.install != undefined;
            }),
        Browser(
            BrowserTypeEnum.Opera,
            DetectionAreaEnum.PROPERTIES_ONLY,
            'opr|opera', 'opr\/|version\/',
            function () {
                return (window.opera != undefined && window.history.navigationMode != undefined) ||
                    (window.opr != undefined && window.opr.addons != undefined
                    && typeof window.opr.addons.installExtension == 'function');
            }),
        Browser(
            BrowserTypeEnum.Chrome,
            DetectionAreaEnum.PROPERTIES_ONLY,
            'chrome', 'chrome\/',
            function () {
                return window.chrome != undefined &&
                    typeof window.chrome.csi == 'function' &&
                    typeof window.chrome.loadTimes == 'function' &&
                    document.webkitHidden != undefined &&
                    (document.webkitHidden == true || document.webkitHidden == false);
            }),
        Browser(
            BrowserTypeEnum.Safari,
            DetectionAreaEnum.PROPERTIES_ONLY,
            'safari|(os |os x )[0-9].*applewebkit', 'version\/',
            function () {
                var p = document.createElement('p');
                p.innerText = '.';
                p.style = 'text-shadow: rgb(99, 116, 171) 20px -12px 2px';

                return ((Object.prototype.toString.call(window.HTMLElement).indexOf('Constructor') > 0) ||
                    (window.webkitAudioPannerNode && window.webkitConvertPointFromNodeToPage)) &&
                    window.innerWidth != undefined && window.innerHeight != undefined && p.style.textShadow != undefined;
            }),
        Browser(
            BrowserTypeEnum.PhantomJS,
            DetectionAreaEnum.PROPERTIES_ONLY,
            '',
            '',
            function () {
                return typeof window.callPhantom === 'function';
            }),
        Browser(
            BrowserTypeEnum.Other,
            DetectionAreaEnum.USER_AGENT_ONLY,
            'mozilla.*android.*applewebkit(?!.*chrome.*)|linux.*android.*applewebkit.* version/.*chrome',
            '',
            null),
        Browser(
            BrowserTypeEnum.Other,
            DetectionAreaEnum.USER_AGENT_ONLY,
            'aol/.*aolbuild/|aolbuild/.*aol/|puffin|maxthon|valve|silk|playstation|playstation|nintendo|wosbrowser',
            '',
            null)
    ];

    var getBrowserVersion = function (browserVersionRegexStr, useragent) {
        var browserVersionRegex;
        var browserVersion = '';

        if (browserVersionRegexStr.length > 0) {
            browserVersionRegex = new RegExp(browserVersionRegexStr + '[0-9]+(?:.[0-9]+)*');
            var match = useragent.match(browserVersionRegex);
            if (match != null && match[0] != null) {
                browserVersion = match[0].replace(useragent.match(new RegExp(browserVersionRegexStr))[0], '');
            }
        }

        return browserVersion;
    };
    
    var isBrowserType = function (browserTypeRegexStr, useragent) {

        var browserTypeRegExp;
        if (browserTypeRegexStr.length > 0) {
            browserTypeRegExp = new RegExp(browserTypeRegexStr);
            return browserTypeRegExp.test(useragent);
        }
    };

    var fillBrowserDetailsByUserAgent = function (ua) {
        var useragent_lowerCase = ua.toLowerCase();
        for (var i = 0; i < BrowsersData.length; i++) {

            if (isBrowserType(BrowsersData[i].userAgentRules.browserTypeRegexStr ,useragent_lowerCase)) {
                BrowsersData[i].userAgentRules.passed = true;
                BrowsersData[i].version = getBrowserVersion(BrowsersData[i].userAgentRules.browserVersionRegexStr, useragent_lowerCase);
            }
        }
    };

    var fillBrowserDetailsByProperties = function () {
        for (var i = 0; i < BrowsersData.length; i++) {
            if (BrowsersData[i].propertiesRules.evaluatePropertiesRule) {
                try {
                    BrowsersData[i].propertiesRules.passed = BrowsersData[i].propertiesRules.evaluatePropertiesRule();
                }
                catch (e) {}
            }
        }
    };

    this.getBrowsersData = function () {
      return BrowsersData;
    };

    this.getBrowserIdAndVersion = function (ua) {
        var browserIdByUserAgent;
        var browserIdByProperties;
        var browserVersion;

        fillBrowserDetailsByUserAgent(ua);
        fillBrowserDetailsByProperties();

        for (var i = 0; i < BrowsersData.length; i++) {

            if (BrowsersData[i].detectionArea == DetectionAreaEnum.USER_AGENT_AND_PROPERTIES) {
                if (BrowsersData[i].userAgentRules.passed == true &&
                    BrowsersData[i].propertiesRules.passed == true) {
                    browserIdByUserAgent = BrowsersData[i].browserID;
                    browserIdByProperties = BrowsersData[i].browserID;
                }
            }
            else if (BrowsersData[i].detectionArea == DetectionAreaEnum.USER_AGENT_ONLY) {
                if (BrowsersData[i].userAgentRules.passed == true) {
                    
                    browserIdByUserAgent = BrowsersData[i].browserID;
                    browserIdByProperties = BrowsersData[i].browserID;
                }
            }
            else {
                if (browserIdByUserAgent == undefined && BrowsersData[i].userAgentRules.passed == true) {
                    browserIdByUserAgent = BrowsersData[i].browserID;
                }
                if (browserIdByProperties == undefined && BrowsersData[i].propertiesRules.passed == true) {
                    browserIdByProperties = BrowsersData[i].browserID;
                }
            }

            if (browserIdByProperties != undefined && browserIdByUserAgent != undefined) {
                break;
            }
        }

        browserVersion = browserIdByProperties === browserIdByUserAgent ? BrowsersData[i].version : '';
        return {
            ID: browserIdByProperties,
            version: browserVersion,
            ID_UA: browserIdByUserAgent
        };
    };
};

function dv_baseHandler(){function Ab(){var a="";try{var c=eval(function(a,c,e,k,f,n){f=function(a){return(a<c?"":f(parseInt(a/c)))+(35<(a%=c)?String.fromCharCode(a+29):a.toString(36))};if(!"".replace(/^/,String)){for(;e--;)n[f(e)]=k[e]||f(e);k=[function(a){return n[a]}];f=function(){return"\\w+"};e=1}for(;e--;)k[e]&&(a=a.replace(RegExp("\\b"+f(e)+"\\b","g"),k[e]));return a}("(19(){1n{1n{3i('1a?1y:1F')}1q(e){v{m:\"-5z\"}}19 3q(1H,2v,21){18(d 1N 5A 1H){w(1N.2u(2v)>-1&&(!21||21(1H[1N])))v 1y}v 1F}19 g(s){d h=\"\",t=\"5B.;j&5C}5y/0:5x'5t=B(5u-5v!,5w)5r\\\\{ >5D+5E\\\"5L<\";18(i=0;i<s.1e;i++)f=s.2t(i),e=t.2u(f),0<=e&&(f=t.2t((e+41)%82)),h+=f;v h}19 1R(2r,1x){1n{w(2r())m.1C((1a==1a.3m?-1:1)*1x)}1q(e){m.1C(-5P*1x);X.1C(1x+\"=\"+(e.5K||\"5J\"))}}d c=['5F\"1r-5G\"5H\"29','p','l','60&p','p','{','\\\\<}4\\\\5I-5s<\"5q\\\\<}4\\\\5a<Z?\"6','e','5b','-5,!u<}\"5c}\"','p','J','-5d}\"<59','p','=o','\\\\<}4\\\\2w\"2f\"y\\\\<}4\\\\2w\"2f\"58}2\"<,u\"<5}?\"6','e','J=',':<54}T}<\"','p','h','\\\\<}4\\\\8-2}\"E(n\"16}b?\\\\<}4\\\\8-2}\"E(n\"2E<N\"[1A*1t\\\\\\\\2I-55<2J\"2O\"56]1i}C\"13','e','57','\\\\<}4\\\\5e;5f||\\\\<}4\\\\5m?\"6','e','+o','\"1f\\\\<}4\\\\2S\"I<-5n\"2x\"5\"5o}2A<}5p\"1f\\\\<}4\\\\1o}1M>1I-1U}2}\"2x\"5\"5l}2A<}5k','e','=J','10}U\"<5}5g\"7}F\\\\<}4\\\\[5h}5i:5j]k}9\\\\<}4\\\\[t:2W\"5Q]k}9\\\\<}4\\\\[5R})5-u<}t]k}9\\\\<}4\\\\[6n]k}9\\\\<}4\\\\[6o}6p]k}6q','e','6m',':6l}<\"H-1L/2M','p','6h','\\\\<}4\\\\12<U/1p}9\\\\<}4\\\\12<U/!k}b','e','=l','1d\\\\<}4\\\\6i}/6j}U\"<5}6k\"7}6r<2B}6s\\\\6z\"6A}/k}2C','e','=S=','\\\\<}4\\\\E-6B\\\\<}4\\\\E-6C\"5\\\\U?\"6','e','+J','\\\\<}4\\\\2z!6y\\\\<}4\\\\2z!6t)p?\"6','e','6u','-}\"6v','p','x{','\\\\<}4\\\\E<2K-6w}6g\\\\<}4\\\\6f\"5Y-5Z\\\\<}4\\\\61.42-2}\"62\\\\<}4\\\\5X<N\"H}5W?\"6','e','+S','10}U\"<5}O\"17\"7}F\\\\<}4\\\\G<1J\"1f\\\\<}4\\\\G<2c}U\"<5}1j\\\\<}4\\\\1m-2.42-2}\"y\\\\<}4\\\\1m-2.42-2}\"1u\"L\"\"M<3y\"3t\"3u<\"<5}3f\"3e\\\\<Z\"3l<W\"3k{3d:3c\\\\3b<1D}3n-3a<}39\"3s\"1v%3z<W\"1v%3r?\"38\"14\"7}34','e','5S','5T:,','p','5U','\\\\<}4\\\\5V\\\\<}4\\\\2y\"2q\\\\<}4\\\\2y\"2j,T}2i+++++1j\\\\<}4\\\\63\\\\<}4\\\\2p\"2q\\\\<}4\\\\2p\"2j,T}2i+++++t','e','6b','\\\\<}4\\\\6c\"1L\"6d}9\\\\<}4\\\\E\\\\6e<M?\"6','e','6a','10}U\"<5}O:69\\\\<}4\\\\8-2}\"1u\".42-2}\"65-66<N\"67<68<6D}C\"3H<4J<3W[<]E\"27\"1r}\"2}\"3X[<]E\"27\"1r}\"2}\"E<}1g&3Y\"1\\\\<}4\\\\2h\\\\3V\\\\<}4\\\\2h\\\\1o}1M>1I-1U}2}\"z<3R-2}\"3S\"2.42-2}\"3T=3Z\"7}40\"7}P=48','e','x','49)','p','+','\\\\<}4\\\\2g:4a<5}47\\\\<}4\\\\2g\"46?\"6','e','3Q','L!!44.45.H 4b','p','x=','\\\\<}4\\\\3I}3D)u\"3E\\\\<}4\\\\3M-2?\"6','e','+=','\\\\<}4\\\\2k\"3N\\\\<}4\\\\2k\"3O--3L<\"2f?\"6','e','x+','\\\\<}4\\\\8-2}\"2l}\"2o<N\"y\\\\<}4\\\\8-2}\"2l}\"2o<N\"3G\")3J\"<:3F\"3K}b?\"6','e','+x','\\\\<}4\\\\2n)u\"3P\\\\<}4\\\\2n)u\"3C?\"6','e','43','\\\\<}4\\\\2m}s<52\\\\<}4\\\\2m}s<4L\" 4M-4N?\"6','e','4O','\\\\<}4\\\\E\"4K-2}\"E(n\"4c<N\"[1A*4F\"4E<4G]4H?\"6','e','+e','\\\\<}4\\\\8-2}\"E(n\"16}b?\\\\<}4\\\\8-2}\"E(n\"4I<:[\\\\4P}}2M][\\\\4Q,5}2]4Y}C\"13','e','4Z','1d\\\\<}4\\\\50}51\\\\<}4\\\\4X$4W','e','4S',':4R<Z','p','4T','\\\\<}4\\\\E-4U\\\\<}4\\\\E-4V}4D\\\\<}4\\\\E-4C<4l?\"6','e','4m','$H:4n}Z!4o','p','+h','\\\\<}4\\\\E\"1T\\\\<}4\\\\E\"1P-4k?\"6','e','4j','1d\\\\<}4\\\\4e:,31}U\"<5}1B\"7}4d<4g<2B}2C','e','4i','\\\\<}4\\\\12<U/4p&2V\"E/2T\\\\<}4\\\\12<U/4q}C\"3o\\\\<}4\\\\12<U/f[&2V\"E/2T\\\\<}4\\\\12<U/4A[S]]2S\"4B}b?\"6','e','4x','4w}4s}4r>2s','p','4t','\\\\<}4\\\\1h:<1Y}s<4u}9\\\\<}4\\\\1h:<1Y}s<4v<}f\"u}2P\\\\<}4\\\\2H\\\\<}4\\\\1h:<1Y}s<C[S]E:2W\"1p}b','e','l{','64\\'<}4\\\\T}6E','p','==','\\\\<}4\\\\G<1J\\\\<}4\\\\G<2d\\\\<Z\"2a\\\\<}4\\\\G<2b<W\"?\"6','e','8A','\\\\<}4\\\\2X}2e-30\"}2Y<8B\\\\<}4\\\\2X}2e-30\"}2Y/2Q?\"6','e','=8x','\\\\<}4\\\\E\"2f\"8t\\\\<}4\\\\8u<8v?\"6','e','o{','\\\\<}4\\\\8w-)2\"2U\"y\\\\<}4\\\\1h-8C\\\\1r}s<C?\"6','e','+l','\\\\<}4\\\\2R-2\"8D\\\\<}4\\\\2R-2\"8L<Z?\"6','e','+{','\\\\<}4\\\\E:8M}9\\\\<}4\\\\8J-8I}9\\\\<}4\\\\E:8E\"<8F\\\\}k}b?\"6','e','{S','\\\\<}4\\\\1l}\"11}8G\"-8H\"2f\"q\\\\<}4\\\\r\"<5}8s?\"6','e','o+',' &H)&8r','p','8d','\\\\<}4\\\\E.:2}\"c\"<8e}9\\\\<}4\\\\8f}9\\\\<}4\\\\8c<}f\"u}2P\\\\<}4\\\\2H\\\\<}4\\\\1o:}\"k}b','e','88','89\"5-\\'2G:2M','p','J{','\\\\<}4\\\\8a\"5-\\'2G:8O}8h=8o:D|q=2F|8p-5|8q--1L/2\"|2N-2F|8i\"=8j\"2f\"q\\\\<}4\\\\1V\"25:24<1D}D?\"6','e','=8k','\\\\<}4\\\\8-2}\"E(n\"16}b?\\\\<}4\\\\8-2}\"E(n\"2E<N\"[1A*1t\\\\\\\\2I-2J\"2O/95<97]1i}C\"13','e','98',')96!93}s<C','p','8T','\\\\<}4\\\\2L<<8U\\\\<}4\\\\2L<<8R<}f\"u}94?\"6','e','{l','\\\\<}4\\\\33.L>g;H\\'T)Y.8P\\\\<}4\\\\33.L>g;8V&&8W>H\\'T)Y.I?\"6','e','l=','1d\\\\<}4\\\\91\\\\92>90}U\"<5}1B\"7}F\"32}U\"<5}8Z\\\\<}4\\\\8X<2K-20\"u\"8Y}U\"<5}1B\"7}F\"32}U\"<5}85','e','{J','H:<Z<:5','p','77','\\\\<}4\\\\k\\\\<}4\\\\E\"78\\\\<}4\\\\r\"<5}3x\"3p}/1j\\\\<}4\\\\8-2}\"3w<}1g&79\\\\<}4\\\\r\"<5}1k\"}u-76=?10}U\"<5}O\"17\"7}75\\\\<}4\\\\1l}\"r\"<5}71\"14\"7}F\"72','e','73','\\\\<}4\\\\1S-U\\\\y\\\\<}4\\\\1S-74\\\\<}4\\\\1S-\\\\<}?\"6','e','7a','7b-N:7i','p','7j','\\\\<}4\\\\1X\"7k\\\\<}4\\\\1X\"86\"<5}7h\\\\<}4\\\\1X\"7g||\\\\<}4\\\\7c?\"6','e','h+','7d<u-7e/','p','{=','\\\\<}4\\\\r\"<5}1k\"}u-7f\\\\<}4\\\\1o}1M>1I-1U}2}\"q\\\\<}4\\\\r\"<5}1k\"}u-2D','e','=S','\\\\<}4\\\\70\"1f\\\\<}4\\\\6Z}U\"<5}1j\\\\<}4\\\\6L?\"6','e','{o','\\\\<}4\\\\6M}<6N\\\\<}4\\\\6K}?\"6','e','=6J','\\\\<}4\\\\G<1J\\\\<}4\\\\G<2d\\\\<Z\"2a\\\\<}4\\\\G<2b<W\"y\"1f\\\\<}4\\\\G<2c}U\"<5}t?\"6','e','J+','c>A','p','=','10}U\"<5}O\"17\"7}F\\\\<}4\\\\E\"6F\"6G:6H}6I^[6O,][6P+]6W\\'<}4\\\\6X\"2f\"q\\\\<}4\\\\E}u-6Y\"14\"7}6V=6U','e','6Q','\\\\<}4\\\\1G:!3g\\\\<}4\\\\8-2}\"E(n\"16}b?\\\\<}4\\\\8-2}\"E(n\"1O<:[f\"29*6R<W\"6S]6T<:[<Z*1t:Z,1Q]1i}C\"13','e','=7l','\\\\<}4\\\\28\"<22-23-u}7m\\\\<}4\\\\28\"<22-23-u}7Q?\"6','e','{x','7R}7K','p','7S','\\\\<}4\\\\8-2}\"E(n\"16}b?\\\\<}4\\\\8-2}\"E(n\"1O<:[<Z*1t:Z,1Q]F:<7P[<Z*7O]1i}C\"13','e','h=','7J-2}\"r\"<5}k}b','e','7L','\\\\<}4\\\\8-2}\"E(n\"16}b?\\\\<}4\\\\8-2}\"E(n\"1O<:[<Z*7M}1Q]R<-C[1A*7T]1i}C\"13','e','81','1d\\\\<}4\\\\26\"\\\\83\\\\<}4\\\\26\"\\\\84','e','80','\\\\<}4\\\\1V\"y\\\\<}4\\\\1V\"25:24<1D}?\"6','e','{e','\\\\<}4\\\\7V}Z<}7W}9\\\\<}4\\\\7X<f\"k}9\\\\<}4\\\\7Y/<}C!!7I<\"42.42-2}\"1p}9\\\\<}4\\\\7H\"<5}k}b?\"6','e','7u','T>;7v\"<4f','p','h{','\\\\<}4\\\\7s<u-7r\\\\7n}9\\\\<}4\\\\1h<}7p}b?\"6','e','7q','\\\\<}4\\\\E\"1T\\\\<}4\\\\E\"1P-35}U\"<5}O\"17\"7}F\\\\<}4\\\\1l}\"r\"<5}1k\"E<}1g&36}3j=y\\\\<}4\\\\1l}\"8-2}\"1u\".42-2}\"7w}\"u<}7x}7E\"14\"7}F\"3h?\"6','e','{h','\\\\<}4\\\\7F\\\\<}4\\\\7G}<(7D?\"6','e','7C','\\\\<}4\\\\7y<U-2Z<7z&p?1d\\\\<}4\\\\7B<U-2Z<8z/31}U\"<5}1B\"7}F\"7A','e','=7o','7t\\'<7Z\"','p','{{','\\\\<}4\\\\E\"1T\\\\<}4\\\\E\"1P-35}U\"<5}O\"17\"7}F\\\\<}4\\\\1l}\"r\"<5}1k\"E<}1g&36}3j=7U\"14\"7}F\"3h?\"6','e','7N','10}U\"<5}O\"17\"7}F\\\\<}4\\\\1G:!3g\\\\<}4\\\\1m-2.42-2}\"y\\\\<}4\\\\1m-2.42-2}\"1u\"L\"\"M<3y\"3t\"3u<\"<5}3f\"3e\\\\<Z\"3l<W\"3k{3d:3c\\\\3b<1D}3n-3a<}39\"3s\"1v%3z<W\"1v%3r?\"38\"14\"7}34','e','{+','\\\\<}4\\\\8S<8N a}8l}9\\\\<}4\\\\E}8m\"8n 8g- 1p}b','e','87','8b\\\\<}4\\\\r\"<5}1G}8K\"5M&M<C<}8y}C\"3o\\\\<}4\\\\r\"<5}3x\"3p}/1j\\\\<}4\\\\8-2}\"4z\\\\<}4\\\\8-2}\"3w<}1g&4y[S]4h=?\"6','e','l+'];d 1w='(19(){d m=[],X=[];'+3q.37()+1R.37()+'';18(d j=0;j<c.1e;j+=3){1w+='1R(19(){v '+(c[j+1]=='p'?'1a[\"'+g(c[j])+'\"]!=3U':g(c[j]))+'}, '+53(g(c[j+2]))+');'}1w+='v {m:m,X:X}})();';d K=[];d 1K=[];d 1c=1a;18(d i=0;i<6x;i++){d V=1c.3i(1w);w(V.X.1e>15){v{m:V.X[0]}}18(d 1b=0;1b<V.m.1e;1b++){d 1z=1F;18(d Q=0;Q<K.1e;Q++){w(K[Q]==V.m[1b]){1z=1y;1s}3B w(1Z.1E(K[Q])==1Z.1E(V.m[1b])){K[Q]=1Z.1E(K[Q]);1z=1y;1s}}w(!1z)K.1C(V.m[1b])}w(1c==1a.3m){1s}3B{1n{w(1c.3v.5O.5N)1c=1c.3v}1q(e){1s}}}d 1W={m:K.3A(\",\")};w(1K.1e>0)1W.X=1K.3A(\"&\");v 1W}1q(e){v{m:\"-8Q\"}}})();",
62,567,"    Z5  Ma2vsu4f2 aM EZ5Ua a44OO  a44  var       P1  res a2MQ0242U    E45Uu    return if  OO        E3 _   results    qD8  ri     currentResults C3 err   qsa  EBM 3RSvsu4f2 U3q2D8M2  5ML44P1 MQ8M2 for function window cri currWindow U5q length QN25sF Z27 E_ WDE42 tOO E35f ENuM2 EsMu try E2 fP1 catch g5 break  EC2 vFoS fc ci true exists fMU q5D8M2 push ZZ2 abs false Eu wnd Tg5 M5OO errors uM U5Z2c prop 5ML44qWZ UT _t ei Euf UIuCTZOO N5 EfaNN_uZf_35f response EuZ ZU5 Math  func _7Z fC_ 2MM _5 zt__  Ea Q42 3OO M5E32 M511tsa M5E 5Mu  E27 z5 Z2711t Q42E EU E_UaMM2 ELZg5 EufB 0UM EuZ_lEf Q42OO fu  charAt indexOf str Ef35M ENM5 EuZ_hEf E_Y Z2s ZP1 a44nD  5ML44qWfUM uZf ALZ02M ELMMuQOO BuZfEU5 kN7 sMu E__   MuU U25sF  E__N Ef2 2Qfq  BV2U uf ENu 2M_  _NuM tzsa QN25sF511tsa EcIT_0 Fsu4f2HnnDqD NTZOOqsa sqtfQ toString Ma2vsu4f2nUu m42s uMC vF3 2Ms45 SN7HF5 2HFB5MZ2MvFSN7HF vFuBf54a 4uQ2MOO Ma2HnnDqD eval uNfQftD11m vFl 3vFJlSN7HF32 top HF 3RSOO vB4u co Ht vFmheSN7HF42s 2qtf Q42tD11tN5f parent EM2s2MM2ME E3M2sP1tuB5a Ba HFM join else ujuM Z42 uOO 2r2 EZ5p5  EA5Cba 2s2MI5pu 35ZP1 MU0 EuZZTsMu 7__OO 7__E2U u_Z2U5Z2OO xJ 1Z5Ua EUM2u tDRm null E2fUuN2z21 sq2 OO2 sqt DM2 PSHM2   oo _ALb A_pLr IQN2 _V5V5OO HnDqD Ld0 2Mf cAA_cg 5MqWfUM F5ENaB4 zt_M  f32M_faB D11m lJ oJ NTZ NLZZM2ff Je V0 7A5C fOO fDE42 fY45 5IMu hx CP1 CF M2 ox squ EM2s2MM2MOO fD aNP1 2MUaMQE sOO kC5 1tk27 UEVft WD 5ML44qtZ 99D uCUuZ2OOZ5Ua CEC2 Mu 2cM4 JJ UmBu Um u_faB Jl hJ 2MUaMQOO 2MUaMQEU5 _tD zt_ tDE42 eS zt__uZ_M f_tDOOU5q COO parseInt ZBu kUM EVft eo r5 u4f ENaBf_uZ_faB xh g5a fgM2Z2 E7LZfKrA 24N2MTZ qD8M2 tf5a ZA2 24t 2Zt QN2P1ta E7GXLss0aBTZIuC 25a QN211ta 2ZtOO QOO  5Zu4 Kt Q6T uic2EHVO LnG s7 YDoMw8FRp3gd94 99 in Ue PzA NhCZ lkSvfxWX C2 Na 2Z0 ENaBf_uZ_uZ unknown message 1bqyJIma  href location 1000 r5Z2t tUZ xx _M he EuZ_hOO 5Z2f EfUM 2TsMu 2OO  EuZZ I5b5ZQOO EuZ_lOO UufUuZ2 fbQIuCpu 2qtfUM tDHs5Mq 1SH uMF21 xo xl Ef aM4P1 2BfM2Z EaNZu U2OO ho zt_4 Mtzsa q5BVD8M2 u_a ee tUBt tB LMMt a44nDqD F5BVEa a44OO5BVEu445 AEBuf2g lS M__ 2_M2s2M2 100 AOO IuMC2 b4u UCMOO UCME i2E42 s5 5NENM5U2ff_ uC_ uMfP1 a44OOk Sh EuZfBQuZf E5U4U5qDEN4uQ ELZ0 N2MOO um Sm xe 1t32 vFSN7t FZ HnnDqD FP 8lzn kE 2DnUu E5U4U511tsa E5U4U5OO E3M2szsu4f2nUu Ma2nnDqDvsu4f2 oS M2sOO FN1 2DRm hh 5NOO sq JS ___U E35aMfUuND _NM _uZB45U 2P1 CfE35aMfUuN OOq _ZBf le CfOO So uC2MOO f2MP1 Sl N4uU2_faUU2ffP1 Jo bM5 ENM LZZ035NN2Mf lo _c bQTZqtMffmU5 2MtD11 EIMuss u60 Ma2nDvsu4f2 ztIMuss ol a2TZ a44HnUu E_NUCOO E_NUCEYp_c Eu445Uu gI Z5Ua  eh 1tB2uU5 Jx 1tfMmN4uQ2Mt Z25 uC2MEUB B24 xS 1tNk4CEN3Nt HnUu E4u CcM4P1 Ef2A ENuM ZC2 lh oe  B__tDOOU5q B_UB_tD tnD CfEf2U lx ll gaf Egaf u1 ErF hl 4P1 ErP1 M5 wZ8 uZf35f DkE SS UP1 _f 5M2f zlnuZf2M UUUN 2N5 rLTp E3M2sD fNNOO E0N2U u4buf2Jl E_Vu Se fzuOOuE42 ubuf2b45U Jh ZOO fN uCOO u_ 2M_f35 a44OOkuZwkwZ8ezhn7wZ8ezhnwE3 4kE fC532M2P1 ENuMu U2f uCEa u_uZ_M2saf2_M2sM2f3P1 4Zf 2MOOkq IOO 999 ZfF EUuU oh ZfOO _I AbL zt af_tzsa tnDOOU5q A_tzsa ztBM5 f2Mc 4Qg5 U25sFLMMuQ kZ 2u4 fN4uQLZfEVft eJ".split(" "),
0,{}));c.hasOwnProperty("err")&&(a=c.err);return{vdcv:25,vdcd:c.res,err:a}}catch(e){return{vdcv:25,vdcd:"0",err:a}}}function ua(a,c,e){var e=e||150,d=window._dv_win||window;if(d.document&&d.document.body)return c&&c.parentNode?c.parentNode.insertBefore(a,c):d.document.body.insertBefore(a,d.document.body.firstChild),!0;if(0<e)setTimeout(function(){ua(a,c,--e)},20);else return!1}function Ra(a){var c=null;try{if(c=a&&a.contentDocument)return c}catch(e){}try{if(c=a.contentWindow&&a.contentWindow.document)return c}catch(d){}try{if(c=
window._dv_win.frames&&window._dv_win.frames[a.name]&&window._dv_win.frames[a.name].document)return c}catch(l){}return null}function Sa(a){var c=document.createElement("iframe");c.name=c.id=window._dv_win.dv_config.emptyIframeID||"iframe_"+Math.floor(1E12*(Math.random()+""));c.width=0;c.height=0;c.style.display="none";c.src=a;return c}function Ta(a){var c={};try{for(var e=RegExp("[\\?&]([^&]*)=([^&#]*)","gi"),d=e.exec(a);null!=d;)"eparams"!==d[1]&&(c[d[1]]=d[2]),d=e.exec(a);return c}catch(l){return c}}
function Bb(a){try{if(1>=a.depth)return{url:"",depth:""};var c,e=[];e.push({win:window._dv_win.top,depth:0});for(var d,l=1,C=0;0<l&&100>C;){try{if(C++,d=e.shift(),l--,0<d.win.location.toString().length&&d.win!=a)return 0==d.win.document.referrer.length||0==d.depth?{url:d.win.location,depth:d.depth}:{url:d.win.document.referrer,depth:d.depth-1}}catch(k){}c=d.win.frames.length;for(var f=0;f<c;f++)e.push({win:d.win.frames[f],depth:d.depth+1}),l++}return{url:"",depth:""}}catch(n){return{url:"",depth:""}}}
function O(a){var c=String(),e,d,l;for(e=0;e<a.length;e++)l=a.charAt(e),d="!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~".indexOf(l),0<=d&&(l="!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~".charAt((d+47)%94)),c+=l;return c}function Cb(){try{return eval(O("W7F?4E:@? 86E|2C<:?8DWXLECJLG2C HlH:?5@HjG2C ?l_jECJLH9:=6WH]A2C6?EUUHPlH]A2C6?EUUH]A2C6?E]5@4F>6?EXLHlH]A2C6?Ej:7W?ZZm`_X3C62<NN42E49W6XLNG2C 3:ED$6El_jG2C 255q:El7F?4E:@?W:[3XL:7W3X3:ED$6ElW3:ED$6EMW`kk:XXmmm_Nj255q:EW`c[H]A=2J6Cx?DE2?46UUH]5@4F>6?E]BF6CJ$6=64E@CWVD4C:AE,DC4YlQ25D\\A=2J6C]4@>Q.VXXj255q:EW`d[H]KAKUUH]KAK]4C62E6!=2J6CXj255q:EW`e[H]IJ04964<DF>UUH]A=2460A=2J6CUUH]=@8;H@?C625JUUH]=@8r@?E6?E!2FD6#6BF6DE65XjC6EFC? 3:ED$6EN42E49W6XLC6EFC? _NNXWXj"))}catch(a){return 0}}
this.createRequest=function(){function a(b,a){var j={};try{if(b.performance&&b.performance.getEntries)for(var e=b.performance.getEntries(),d=0;d<e.length;d++){var f=e[d],g=f.name.match(/.*\/(.+?)\./);if(g&&g[1]){var l=g[1].replace(/\d+$/,""),D=a[l];if(D){for(var k=0;k<D.stats.length;k++){var h=D.stats[k];j[D.prefix+h.prefix]=Math.round(f[h.name])}delete a[l];if(!c(a))break}}}return j}catch(n){}}function c(b){var a=0,c;for(c in b)b.hasOwnProperty(c)&&++a;return a}window._dv_win.$dv.isEval=1;window._dv_win.$dv.DebugInfo=
{};var e=!1,d=!1,l,C,k=!1,f=window._dv_win,n=0,Qa=!1,va=getCurrentTime();window._dv_win.t2tTimestampData=[{dvTagCreated:va}];var P;try{for(P=0;10>=P;P++)if(null!=f.parent&&f.parent!=f)if(0<f.parent.location.toString().length)f=f.parent,n++,k=!0;else{k=!1;break}else{0==P&&(k=!0);break}}catch(Yb){k=!1}var B;0==f.document.referrer.length?B=f.location:k?B=f.location:(B=f.document.referrer,Qa=!0);var Ua="",wa=null,xa=null;try{window._dv_win.external&&(wa=void 0!=window._dv_win.external.QueuePageID?window._dv_win.external.QueuePageID:
null,xa=void 0!=window._dv_win.external.CrawlerUrl?window._dv_win.external.CrawlerUrl:null)}catch(Ra){Ua="&dvp_extErr=1"}if(!window._dv_win._dvScriptsInternal||!window._dv_win.dvProcessed||0==window._dv_win._dvScriptsInternal.length)return null;var X=window._dv_win._dvScriptsInternal.pop(),K=X.script;this.dv_script_obj=X;this.dv_script=K;window._dv_win.t2tTimestampData[0].dvWrapperLoadTime=X.loadtime;window._dv_win.dvProcessed.push(X);var b=K.src;this.dv_script_obj.dvSrc=b;var m;if(void 0!=window._dv_win.$dv.CommonData.BrowserId&&
void 0!=window._dv_win.$dv.CommonData.BrowserVersion&&void 0!=window._dv_win.$dv.CommonData.BrowserIdFromUserAgent)m={ID:window._dv_win.$dv.CommonData.BrowserId,version:window._dv_win.$dv.CommonData.BrowserVersion,ID_UA:window._dv_win.$dv.CommonData.BrowserIdFromUserAgent};else{var Va=dv_GetParam(b,"useragent");m=(new BrowserDetector).getBrowserIdAndVersion(Va?decodeURIComponent(Va):navigator.userAgent);window._dv_win.$dv.CommonData.BrowserId=m.ID;window._dv_win.$dv.CommonData.BrowserVersion=m.version;
window._dv_win.$dv.CommonData.BrowserIdFromUserAgent=m.ID_UA}var E,ya=!0,za=window.parent.postMessage&&window.JSON,Wa=!1;if("0"==dv_GetParam(b,"t2te")||window._dv_win.dv_config&&!0===window._dv_win.dv_config.supressT2T)Wa=!0;if(za&&!1===Wa&&5!=window._dv_win.$dv.CommonData.BrowserId)try{E=Sa(window._dv_win.dv_config.t2turl||"https://cdn3.doubleverify.com/t2tv7.html"),ya=ua(E)}catch(Zb){}window._dv_win.$dv.DebugInfo.dvp_HTML5=za?"1":"0";var Y=dv_GetParam(b,"region")||"",Z;Z=(/iPhone|iPad|iPod|\(Apple TV|iOS|Coremedia|CFNetwork\/.*Darwin/i.test(navigator.userAgent)||
navigator.vendor&&"apple, inc."===navigator.vendor.toLowerCase())&&!window.MSStream;var Aa;if(Z)Aa="https:";else{var Xa="http:";"http:"!=window._dv_win.location.protocol&&(Xa="https:");Aa=Xa}var Db=Aa,Ba;if(Z)Ba="https:";else{var Ya="http:";if("https"==b.match("^https")&&("http"!=window._dv_win.location.toString().match("^http")||"https"==window._dv_win.location.toString().match("^https")))Ya="https:";Ba=Ya}var $=Ba,Za="0";"https:"===$&&(Za="1");try{for(var Eb=f,Ca=f,Da=0;10>Da&&Ca!=window._dv_win.top;)Da++,
Ca=Ca.parent;Eb.depth=Da;var $a=Bb(f);dv_aUrlParam="&aUrl="+encodeURIComponent($a.url);dv_aUrlDepth="&aUrlD="+$a.depth;dv_referrerDepth=f.depth+n;Qa&&f.depth--}catch($b){dv_aUrlDepth=dv_aUrlParam=dv_referrerDepth=f.depth=""}for(var ab=dv_GetDynamicParams(b,"dvp"),aa=dv_GetDynamicParams(b,"dvpx"),ba=0;ba<aa.length;ba++){var bb=dv_GetKeyValue(aa[ba]);aa[ba]=bb.key+"="+encodeURIComponent(bb.value)}"41"==Y&&(Y=50>100*Math.random()?"41":"8",ab.push("dvp_region="+Y));var cb=ab.join("&"),db=aa.join("&"),
Fb=window._dv_win.dv_config.tpsAddress||"tps"+Y+".doubleverify.com",Q="visit.js";switch(dv_GetParam(b,"dvapi")){case "1":Q="dvvisit.js";break;case "5":Q="query.js";break;default:Q="visit.js"}window._dv_win.$dv.DebugInfo.dvp_API=Q;for(var ca="ctx cmp ipos sid plc adid crt btreg btadsrv adsrv advid num pid crtname unit chnl uid scusrid tagtype sr dt dup app dvvidver".split(" "),p=[],v=0;v<ca.length;v++){var Ea=dv_GetParam(b,ca[v])||"";p.push(ca[v]+"="+Ea);""!==Ea&&(window._dv_win.$dv.DebugInfo["dvp_"+
ca[v]]=Ea)}for(var Fa="turl icall dv_callback useragent xff timecheck seltag sadv ord litm scrt invs splc adu native gmnpo".split(" "),v=0;v<Fa.length;v++){var eb=dv_GetParam(b,Fa[v]);null!=eb&&p.push(Fa[v]+"="+(eb||""))}var fb=dv_GetParam(b,"isdvvid")||"";fb&&p.push("isdvvid=1");var gb=dv_GetParam(b,"tagtype")||"",r=window._dv_win.$dv.getMraid(),Ga;a:{try{if("object"==typeof window.$ovv||"object"==typeof window.parent.$ovv){Ga=!0;break a}}catch(ac){}Ga=!1}var Ha=dv_GetParam(b,"sup")||"";try{var hb=
!1,ib=!1;try{var Gb=window.document.getElementById("aolVideoContainer")||window.MmJsBridge&&window.MmJsBridge.vpaid,hb=null!=window.mmSdkVersion,ib=null!=Gb}catch(bc){}if(hb||ib)Ha="mm";else{var jb=!1;null!=r&&("function"===typeof r.getVendor&&"function"===typeof r.getVendorVersion&&"AdMarvel"==r.getVendor())&&(jb=!0);jb&&(Ha="opm")}}catch(cc){}p.push("sup="+Ha);if(1!=fb&&!r&&("video"==gb||"1"==gb)){var kb=dv_GetParam(b,"adid")||"";"function"===typeof _dv_win[kb]&&(p.push("prplyd=1"),p.push("DVP_GVACB="+
kb),p.push("isdvvid=1"));var lb="AICB_"+(window._dv_win.dv_config&&window._dv_win.dv_config.dv_GetRnd?window._dv_win.dv_config.dv_GetRnd():dv_GetRnd());window._dv_win[lb]=function(b){e=!0;l=b;window._dv_win.$dv&&!0==d&&window._dv_win.$dv.registerEventCall(C,{prplyd:0,dvvidver:b})};p.push("AICB="+lb);var Hb=p.join("&"),mb=window._dv_win.document.createElement("script");mb.src=$+"//cdn.doubleverify.com/dvvid_src.js?"+Hb;window._dv_win.document.body.appendChild(mb)}try{var R=a(window,{dvtp_src:{prefix:"d",
stats:[{name:"fetchStart",prefix:"fs"},{name:"duration",prefix:"dur"}]},dvtp_src_internal:{prefix:"dv",stats:[{name:"duration",prefix:"dur"}]}});if(!R||!c(R))p.push("dvp_noperf=1");else for(var Ia in R)R.hasOwnProperty(Ia)&&p.push(Ia+"="+R[Ia])}catch(dc){}var Ib=p.join("&"),F;var Jb=function(){try{return!!window.sessionStorage}catch(b){return!0}},Kb=function(){try{return!!window.localStorage}catch(b){return!0}},Lb=function(){var b=document.createElement("canvas");if(b.getContext&&b.getContext("2d")){var a=
b.getContext("2d");a.textBaseline="top";a.font="14px 'Arial'";a.textBaseline="alphabetic";a.fillStyle="#f60";a.fillRect(0,0,62,20);a.fillStyle="#069";a.fillText("!image!",2,15);a.fillStyle="rgba(102, 204, 0, 0.7)";a.fillText("!image!",4,17);return b.toDataURL()}return null};try{var w=[];w.push(["lang",navigator.language||navigator.browserLanguage]);w.push(["tz",(new Date).getTimezoneOffset()]);w.push(["hss",Jb()?"1":"0"]);w.push(["hls",Kb()?"1":"0"]);w.push(["odb",typeof window.openDatabase||""]);
w.push(["cpu",navigator.cpuClass||""]);w.push(["pf",navigator.platform||""]);w.push(["dnt",navigator.doNotTrack||""]);w.push(["canv",Lb()]);var s=w.join("=!!!=");if(null==s||""==s)F="";else{for(var S=function(b){for(var a="",c,e=7;0<=e;e--)c=b>>>4*e&15,a+=c.toString(16);return a},Mb=[1518500249,1859775393,2400959708,3395469782],s=s+String.fromCharCode(128),G=Math.ceil((s.length/4+2)/16),H=Array(G),q=0;q<G;q++){H[q]=Array(16);for(var I=0;16>I;I++)H[q][I]=s.charCodeAt(64*q+4*I)<<24|s.charCodeAt(64*
q+4*I+1)<<16|s.charCodeAt(64*q+4*I+2)<<8|s.charCodeAt(64*q+4*I+3)}H[G-1][14]=8*(s.length-1)/Math.pow(2,32);H[G-1][14]=Math.floor(H[G-1][14]);H[G-1][15]=8*(s.length-1)&4294967295;for(var da=1732584193,ea=4023233417,fa=2562383102,ga=271733878,ha=3285377520,t=Array(80),L,u,z,A,ia,q=0;q<G;q++){for(var g=0;16>g;g++)t[g]=H[q][g];for(g=16;80>g;g++)t[g]=(t[g-3]^t[g-8]^t[g-14]^t[g-16])<<1|(t[g-3]^t[g-8]^t[g-14]^t[g-16])>>>31;L=da;u=ea;z=fa;A=ga;ia=ha;for(g=0;80>g;g++){var nb=Math.floor(g/20),Nb=L<<5|L>>>27,
M;c:{switch(nb){case 0:M=u&z^~u&A;break c;case 1:M=u^z^A;break c;case 2:M=u&z^u&A^z&A;break c;case 3:M=u^z^A;break c}M=void 0}var Ob=Nb+M+ia+Mb[nb]+t[g]&4294967295;ia=A;A=z;z=u<<30|u>>>2;u=L;L=Ob}da=da+L&4294967295;ea=ea+u&4294967295;fa=fa+z&4294967295;ga=ga+A&4294967295;ha=ha+ia&4294967295}F=S(da)+S(ea)+S(fa)+S(ga)+S(ha)}}catch(ec){F=null}F=null!=F?"&aadid="+F:"";var ob=b,Pb=window._dv_win.dv_config.visitJSURL||$+"//"+Fb+"/"+Q,Qb=Z?"&dvf=0":"",ja;a:{var N=window._dv_win,pb=0;try{for(;10>pb;){if(N.maple&&
"object"===typeof N.maple){ja=!0;break a}if(N==N.parent){ja=!1;break a}pb++;N=N.parent}}catch(fc){}ja=!1}var Rb=ja?"&dvf=1":"",b=Pb+"?"+Ib+"&dvtagver=6.1.src&srcurlD="+f.depth+"&curl="+(null==xa?"":encodeURIComponent(xa))+"&qpgid="+(null==wa?"":wa)+"&ssl="+Za+Qb+Rb+"&refD="+dv_referrerDepth+"&htmlmsging="+(za?"1":"0")+F+Ua;r&&(b+="&ismraid=1");Ga&&(b+="&isovv=1");var Sb=b,h="";try{var x=window._dv_win,h=h+("&chro="+(void 0===x.chrome?"0":"1")),h=h+("&hist="+(x.history?x.history.length:"")),h=h+("&winh="+
x.innerHeight),h=h+("&winw="+x.innerWidth),h=h+("&wouh="+x.outerHeight),h=h+("&wouw="+x.outerWidth);x.screen&&(h+="&scah="+x.screen.availHeight,h+="&scaw="+x.screen.availWidth)}catch(gc){}b=Sb+(h||"");"http:"==b.match("^http:")&&"https"==window._dv_win.location.toString().match("^https")&&(b+="&dvp_diffSSL=1");var qb=K&&K.parentElement&&K.parentElement.tagName&&"HEAD"===K.parentElement.tagName;if(!1===ya||qb)b+="&dvp_isBodyExistOnLoad="+(ya?"1":"0"),b+="&dvp_isOnHead="+(qb?"1":"0");cb&&(b+="&"+cb);
db&&(b+="&"+db);var T="srcurl="+encodeURIComponent(B);window._dv_win.$dv.DebugInfo.srcurl=B;var ka;var la=window._dv_win[O("=@42E:@?")][O("2?46DE@C~C:8:?D")];if(la&&0<la.length){var Ja=[];Ja[0]=window._dv_win.location.protocol+"//"+window._dv_win.location.hostname;for(var ma=0;ma<la.length;ma++)Ja[ma+1]=la[ma];ka=Ja.reverse().join(",")}else ka=null;ka&&(T+="&ancChain="+encodeURIComponent(ka));var U=dv_GetParam(b,"uid");null==U?(U=dv_GetRnd(),b+="&uid="+U):(U=dv_GetRnd(),b=b.replace(/([?&]uid=)(?:[^&])*/i,
"$1"+U));var na=4E3;/MSIE (\d+\.\d+);/.test(navigator.userAgent)&&7>=new Number(RegExp.$1)&&(na=2E3);var rb=navigator.userAgent.toLowerCase();if(-1<rb.indexOf("webkit")||-1<rb.indexOf("chrome")){var sb="&referrer="+encodeURIComponent(window._dv_win.location);b.length+sb.length<=na&&(b+=sb)}if(navigator&&navigator.userAgent){var tb="&navUa="+encodeURIComponent(navigator.userAgent);b.length+tb.length<=na&&(b+=tb)}dv_aUrlParam.length+dv_aUrlDepth.length+b.length<=na&&(b+=dv_aUrlDepth,T+=dv_aUrlParam);
var oa=Ab(),b=b+("&vavbkt="+oa.vdcd),b=b+("&lvvn="+oa.vdcv),b=b+("&"+this.getVersionParamName()+"="+this.getVersion()),b=b+("&eparams="+encodeURIComponent(O(T)));""!=oa.err&&(b+="&dvp_idcerr="+encodeURIComponent(oa.err));m.ID&&(b+="&brid="+m.ID+"&brver="+m.version+"&bridua="+m.ID_UA+"&bds=1",window._dv_win.$dv.DebugInfo.dvp_BRID=m.ID,window._dv_win.$dv.DebugInfo.dvp_BRVR=m.version,window._dv_win.$dv.DebugInfo.dvp_BRIDUA=m.ID_UA);var V;void 0!=window._dv_win.$dv.CommonData.Scenario?V=window._dv_win.$dv.CommonData.Scenario:
(V=this.getTrafficScenarioType(window._dv_win),window._dv_win.$dv.CommonData.Scenario=V);b+="&tstype="+V;window._dv_win.$dv.DebugInfo.dvp_TS=V;var pa="";try{window.top==window?pa="1":window.top.location.host==window.location.host&&(pa="2")}catch(hc){pa="3"}var qa=window._dv_win.document.visibilityState,ub=function(){var a=!1;try{a=r&&"function"===typeof r.getState&&"loading"===r.getState()}catch(c){b+="&dvp_mrgsf=1"}return a},Ka=ub();if("prerender"===qa||Ka)b+="&prndr=1",Ka&&(b+="&dvp_mrprndr=1");
var vb="dvCallback_"+(window._dv_win.dv_config&&window._dv_win.dv_config.dv_GetRnd?window._dv_win.dv_config.dv_GetRnd():dv_GetRnd()),Tb=this.dv_script;window._dv_win[vb]=function(i,f,j,g){var k=getCurrentTime();d=!0;C=j;f.$uid=j;var h=Ta(ob);i.tags.add(j,h);h=Ta(b);i.tags[j].set(h);i.tags[j].beginVisitCallbackTS=k;i.tags[j].set({tagElement:Tb,dv_protocol:$,protocol:Db,uid:j});i.tags[j].ImpressionServedTime=getCurrentTime();i.tags[j].getTimeDiff=function(){return(new Date).getTime()-this.ImpressionServedTime};
try{"undefined"!=typeof g&&null!==g&&(i.tags[j].ServerPublicDns=g),i.tags[j].adServingScenario=pa,i.tags[j].t2tIframeCreationTime=va,i.tags[j].t2tProcessed=!1,i.tags[j].t2tIframeId=E.id,i.tags[j].t2tIframeWindow=E.contentWindow,$dv.t2tEventDataZombie[E.id]&&(i.tags[j].uniquePageViewId=$dv.t2tEventDataZombie[E.id].uniquePageViewId,$dv.processT2TEvent($dv.t2tEventDataZombie[E.id],i.tags[j]))}catch(n){}i.messages&&i.messages.startSendingEvents&&i.messages.startSendingEvents(f,j);!0==e&&i.registerEventCall(j,
{prplyd:0,dvvidver:l});var B=function(){var a=window._dv_win.document.visibilityState;"prerender"===qa&&("prerender"!==a&&"unloaded"!==a)&&(qa=a,i.tags[j].set({prndr:0}),i.registerEventCall(j,{prndr:0}),i&&i.pubSub&&i.pubSub.publishHistoryRtnEvent(j),window._dv_win.document.removeEventListener(m,B))},D=function(){"function"===typeof r.removeEventListener&&r.removeEventListener("ready",D);i.tags[j].set({prndr:0});i.registerEventCall(j,{prndr:0});i&&i.pubSub&&i.pubSub.publishHistoryRtnEvent(j)};if("prerender"===
qa)if(f=window._dv_win.document.visibilityState,"prerender"!==f&&"unloaded"!==f)i.tags[j].set({prndr:0}),i.registerEventCall(j,{prndr:0}),i&&i.pubSub&&i.pubSub.publishHistoryRtnEvent(j);else{var m;"undefined"!==typeof window._dv_win.document.hidden?m="visibilitychange":"undefined"!==typeof window._dv_win.document.mozHidden?m="mozvisibilitychange":"undefined"!==typeof window._dv_win.document.msHidden?m="msvisibilitychange":"undefined"!==typeof window._dv_win.document.webkitHidden&&(m="webkitvisibilitychange");
window._dv_win.document.addEventListener(m,B,!1)}else Ka&&(ub()?"function"===typeof r.addEventListener&&r.addEventListener("ready",D):(i.tags[j].set({prndr:0}),i.registerEventCall(j,{prndr:0}),i&&i.pubSub&&i.pubSub.publishHistoryRtnEvent(j)));try{var p;a:{var f=window,g={visit:{prefix:"v",stats:[{name:"duration",prefix:"dur"}]}},q;if(f.frames)for(k=0;k<f.frames.length;k++)if((q=a(f.frames[k],g))&&c(q)){p=q;break a}p=void 0}p&&$dv.registerEventCall(j,p)}catch(s){}};var ra;try{var La=0,sa=function(a,
b){b&&32>a&&(La=(La|1<<a)>>>0)},Ub=function(a,b){return function(){return a.apply(b,arguments)}},Vb="svg"===document.documentElement.nodeName.toLowerCase(),wb=function(){return"function"!==typeof document.createElement?document.createElement(arguments[0]):Vb?document.createElementNS.call(document,"http://www.w3.org/2000/svg",arguments[0]):document.createElement.apply(document,arguments)},Wb=["Moz","O","ms","Webkit"],Xb=["moz","o","ms","webkit"],y={style:wb("modernizr").style},Ma=function(a,b,c,e,
f){var d=a.charAt(0).toUpperCase()+a.slice(1),g=(a+" "+Wb.join(d+" ")+d).split(" ");if("string"===typeof b||"undefined"===typeof b){a:{c=g;a=function(){k&&(delete y.style,delete y.modElem)};f="undefined"===typeof f?!1:f;if("undefined"!==typeof e&&(d=nativeTestProps(c,e),"undefined"!==typeof d)){b=d;break a}for(var k,h,l,d=["modernizr","tspan","samp"];!y.style&&d.length;)k=!0,y.modElem=wb(d.shift()),y.style=y.modElem.style;g=c.length;for(d=0;d<g;d++)if(h=c[d],l=y.style[h],~(""+h).indexOf("-")&&(h=
cssToDOM(h)),void 0!==y.style[h])if(!f&&"undefined"!==typeof e){try{y.style[h]=e}catch(m){}if(y.style[h]!=l){a();b="pfx"==b?h:!0;break a}}else{a();b="pfx"==b?h:!0;break a}a();b=!1}return b}g=(a+" "+Xb.join(d+" ")+d).split(" ");for(h in g)if(g[h]in b){if(!1===c)return g[h];e=b[g[h]];return"function"===typeof e?Ub(e,c||b):e}return!1};sa(0,!0);var Na;var J="requestFileSystem",xb=window;0===J.indexOf("@")?Na=atRule(J):(-1!=J.indexOf("-")&&(J=cssToDOM(J)),Na=xb?Ma(J,xb,void 0):Ma(J,"pfx"));sa(1,!!Na);
sa(2,window.CSS?"function"==typeof window.CSS.escape:!1);sa(3,Ma("shapeOutside","content-box",!0));ra=La}catch(ic){ra=0}ra&&(b+="&m1="+ra);var yb=Cb();yb&&(b+="&bsig="+yb);for(var zb,ta="auctionid vermemid source buymemid anadvid ioid cpgid cpid sellerid pubid advcode iocode cpgcode cpcode pubcode prcpaid auip auua".split(" "),Oa=[],W=0;W<ta.length;W++){var Pa=dv_GetParam(ob,ta[W]);null!=Pa&&(Oa.push("dvp_"+ta[W]+"="+Pa),Oa.push(ta[W]+"="+Pa))}(zb=Oa.join("&"))&&(b+="&"+zb);return b+"&jsCallback="+
vb};this.sendRequest=function(a){window._dv_win.t2tTimestampData.push({beforeVisitCall:getCurrentTime()});var c=this.dv_script_obj&&this.dv_script_obj.injScripts,e=this.dv_script_obj&&this.dv_script_obj.srcLocation,d=this.dv_script_obj&&this.dv_script_obj.dvSrc,l=this.getVersionParamName(),C=this.getVersion(),k=window._dv_win.dv_config=window._dv_win.dv_config||{};k.tpsErrAddress=k.tpsAddress||"tps30.doubleverify.com";k.cdnAddress=k.cdnAddress||"cdn.doubleverify.com";var f={};f[l]=C;f.dvp_jsErrUrl=
a;f.dvp_jsErrMsg=encodeURIComponent("Error loading visit.js");l=dv_CreateAndGetErrorImp(k.tpsErrAddress+"/visit.jpg?ctx=818052&cmp=1619415&dvtagver=6.1.src&dvp_isLostImp=1",f);c='<html><head><script type="text/javascript">('+function(a){try{window.dvSrc=a,window.$dv=window.$dv||parent.$dv,window.$dv.dvObjType="dv",window.$frmId=Math.random().toString(36)+Math.random().toString(36)}catch(c){}}.toString()+')("'+d+'");<\/script></head><body><script type="text/javascript">('+(c||"function() {}")+')("'+
e+'");<\/script><script type="text/javascript" id="TPSCall" src="'+a+'"><\/script><script type="text/javascript">('+function(a){var c=document.getElementById("TPSCall");try{c.onerror=function(){try{(new Image).src=a}catch(c){}}}catch(d){}c&&c.readyState?(c.onreadystatechange=function(){"complete"==c.readyState&&document.close()},"complete"==c.readyState&&document.close()):document.close()}.toString()+')("'+l+'");<\/script></body></html>';a=Sa("about:blank");e=a.id.replace("iframe_","");a.setAttribute&&
a.setAttribute("data-dv-frm",e);ua(a,this.dv_script);if(this.dv_script){this.dv_script.id="script_"+e;var e=this.dv_script,n;a:{d=null;try{if(d=a.contentWindow){n=d;break a}}catch(O){}try{if(d=window._dv_win.frames&&window._dv_win.frames[a.name]){n=d;break a}}catch(va){}n=null}e.dvFrmWin=n}if(n=Ra(a))n.open(),n.write(c);else{try{document.domain=document.domain}catch(P){}n=encodeURIComponent(c.replace(/'/g,"\\'").replace(/\n|\r\n|\r/g,""));a.src='javascript: (function(){document.open();document.domain="'+
window.document.domain+"\";document.write('"+n+"');})()"}return!0};this.isApplicable=function(){return!0};this.onFailure=function(){window._dv_win._dvScriptsInternal.unshift(this.dv_script_obj);var a=window._dv_win.dvProcessed,c=this.dv_script_obj;null!=a&&(void 0!=a&&c)&&(c=a.indexOf(c),-1!=c&&a.splice(c,1));return window._dv_win.$dv.DebugInfo};this.getTrafficScenarioType=function(a){var a=a||window,c=a._dv_win.$dv.Enums.TrafficScenario;try{if(a.top==a)return c.OnPage;for(var e=0;a.parent!=a&&1E3>
e;){if(a.parent.document.domain!=a.document.domain)return c.CrossDomain;a=a.parent;e++}return c.SameDomain}catch(d){}return c.CrossDomain};this.getVersionParamName=function(){return"jsver"};this.getVersion=function(){return"139"}};


function dv_src_main(dv_baseHandlerIns, dv_handlersDefs) {

    this.baseHandlerIns = dv_baseHandlerIns;
    this.handlersDefs = dv_handlersDefs;

    this.exec = function () {
        try {
            window._dv_win = (window._dv_win || window);
            window._dv_win.$dv = (window._dv_win.$dv || new dvType());

            window._dv_win.dv_config = window._dv_win.dv_config || {};
            window._dv_win.dv_config.tpsErrAddress = window._dv_win.dv_config.tpsAddress || 'tps30.doubleverify.com';

            var errorsArr = (new dv_rolloutManager(this.handlersDefs, this.baseHandlerIns)).handle();
            if (errorsArr && errorsArr.length > 0) {
                dv_SendErrorImp(window._dv_win.dv_config.tpsErrAddress + '/visit.jpg?ctx=818052&cmp=1619415&dvtagver=6.1.src', errorsArr);
            }
        }
        catch (e) {
            try {
                dv_SendErrorImp(window._dv_win.dv_config.tpsErrAddress + '/visit.jpg?ctx=818052&cmp=1619415&dvtagver=6.1.src&jsver=0&dvp_isLostImp=1', {dvp_jsErrMsg: encodeURIComponent(e)});
            } catch (e) { }
        }
    };
}

try {
    window._dv_win = window._dv_win || window;
    var dv_baseHandlerIns = new dv_baseHandler();
	

    var dv_handlersDefs = [];
    (new dv_src_main(dv_baseHandlerIns, dv_handlersDefs)).exec();
} catch (e) { }