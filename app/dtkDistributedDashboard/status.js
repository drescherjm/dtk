function url(check_tunnel)
{
    if (check_tunnel && tunnel.checked) {
        return "http://localhost:" +controller.defaultPort()
    } else {
        return combo.currentText + ":" +controller.defaultPort()
    }
}
function policy()
{
    return comboPolicies.currentText
}

function setWalltime(hours, min, sec)
{
    return hours + ":" + min +":" + sec ;
}

function submit(nodes, cores, walltime)
{
    console.debug("submit " + cores + " nodes " +nodes )
    var xhr = new XMLHttpRequest();
    xhr.open("PUT", url(true) +"/job", true);
    // timeout doesn't work in qml ?
    xhr.timeout = 5;
    xhr.ontimeout = function () { console.debug("Timeout !!!" )}
    xhr.onreadystatechange = function()
    {
        if ( xhr.readyState == xhr.DONE)
        {
            if ( xhr.status == 201)
            {
                var jobid = xhr.getResponseHeader("X-DTK-JobId");
                console.debug("jobid is " + jobid )
                jobModel.append({"id": jobid,
                                 "user": "me",
                                 "nodes" : NaN,
                                 "cores" : NaN,
                                 "queue" : "unknown"})

            } else {
                console.debug("bad status " + xhr.status )
            }
        }
    }

    xhr.setRequestHeader("Content-Type", "application/json;charset=UTF-8");
    var resources = {  "resources": {"nodes": nodes, "cores": cores },
                       "walltime": walltime,
                       "application": "dtkDistributedSlave --server " + url(false) + " --policy " + policy()
                    }
    xhr.send(JSON.stringify(resources))
}

function show()
{
    var xhr = new XMLHttpRequest();
    xhr.open("GET", url(true) +"/status",true);
    xhr.onreadystatechange = function()
    {
        if ( xhr.readyState == xhr.DONE)
        {
            if ( xhr.status == 200)
            {
                console.debug("status OK, parse" )
                var jsonObject = JSON.parse(xhr.responseText);
                var cores = 0
                var cores_busy = 0
                var nodes_free = 0
                var nodes_busy = 0
                var nodes_down = 0
                for ( var index in jsonObject.nodes ) {
                    cores += jsonObject.nodes[index].cores.length;
                    cores_busy += jsonObject.nodes[index].cores_busy;
                    if (jsonObject.nodes[index].state == "free") {
                        nodes_free ++;
                    } else if (jsonObject.nodes[index].state == "down") {
                        nodes_down ++;
                    } else if (jsonObject.nodes[index].state == "busy") {
                        nodes_busy ++;
                    }
                }
                cores -= cores_busy
                cores_pie.chartData = [{value: cores, color: "green"}, {value: cores_busy, color: "orange"}];
                cores_pie.repaint();
                nodes_pie.chartData = [{value: nodes_free, color: "green"},
                                       {value: nodes_busy, color: "orange"},
                                       {value: nodes_down, color: "red"}];
                nodes_pie.repaint();
                console.debug("cores " + cores )
                console.debug("cores busy " + cores_busy )
                console.debug("nodes free " + nodes_free )
                console.debug("nodes busy " + nodes_busy )
                console.debug("nodes dead " + nodes_down )

                jobModel.clear()
                for ( var index in jsonObject.jobs ) {
                    jobModel.append({"id": jsonObject.jobs[index].id,
                                     "user": jsonObject.jobs[index].username,
                                     "nodes" : jsonObject.jobs[index].resources.nodes,
                                     "cores" : jsonObject.jobs[index].resources.cores,
                                     "queue" : jsonObject.jobs[index].queue })
                }
            } else {
                console.debug("status NOK" + xhr.status)
            }
        }
    }
    xhr.send();
}
