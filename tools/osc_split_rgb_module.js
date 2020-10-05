var rgbValue = [0, 0, 0]

module.exports = {

    oscOutFilter:function(data){

        var {address, args, host, port, clientId} = data
        
        // split
        var res = address.match('.*rgb')
        // FULL MATCH only
        if ( res!= null && res[0] == address ) {

            send(host, port, address + "_r", args[0].value)
            send(host, port, address + "_g", args[1].value)
            send(host, port, address + "_b", args[2].value)

            return // bypass original message
        } 

        return {address, args, host, port}
    }

}