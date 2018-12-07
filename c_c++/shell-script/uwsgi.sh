#!/bin/bash
# ©linnovs
# convert python to unix process => tirggered by unix socket => not triggered by http anymore
# nginx config => whern there quest => unix call app.py => when idle 30 min=> unix kill pytho => trigger unix port => unix process
# engix wont die because its c not interpreter, unless overload

# WSGI: python spec that defines standard interface for communication between framework n server

# uWSGI: application server container, full stack for deploying applications and service, communicate using WSGI spec
# uWSGI server translate request to application using WSGI spec

# uwsgi: wire protocol (not transport protocol), binary protocol to communicate w server 
# https://www.digitalocean.com/community/tutorials/how-to-set-up-uwsgi-and-nginx-to-serve-python-apps-on-ubuntu-14-04

VERSION='0.0.1'
APPNAME='uwsgi-python-app'
APPPATH="/opt/$APPNAME"
CONFIG_DIR="/etc/uwsgi"
USER="nginx"
GROUP="nginx"
NUM=10
DEBUG=0
LOG=0
SERVICE=0

usage() {
    echo 
    echo "usage: ${0##*/} [-vVh|--version|--help|--verbose] <option> [sub option] <app> [args...]"
    echo
    echo "${0##*/} is a management script for nginx's python uwsgi service(systemd)."
    echo
    echo "options:"
    echo "  manage                                 manage created app in this server"
    echo "    sub options:"
    echo "      start                              start <app> service"
    echo "      stop                               stop <app> service"
    echo "      restart                            restart <app> service"
    echo "      status                             get <app> service status"
    echo "      log                                print latest 10 line of "
    echo "                                         <app> log"
    echo "        args:"
    echo "          -f                             watch for <app> service log"
    echo "          -n <num>                       print latest <num> line of <app> log"
    echo
    echo "  create,                                create a new service using <app>"
    echo "  update,                                update the src code to new version"
    echo "  remove                                 remove the service"
    echo "    args:"
    echo "      --ini <script path>                the ini file for the uwsgi. if --ini"
    echo "                                         is provided, it will read from the script file"
    echo "                                         defulat: ./uwsgi.conf.<app>.ini"
    echo "      -P, --path                         the path of the production version directory"
    echo "                                         default: /opt/<app>"
    echo "      --permission <user:group>          the user and group name of nginx, "
    echo "                                         default: nginx:nginx"
    echo
    echo "  --generate-config                      generate a config file to "
    echo "                                         $PWD/uwsgi.conf.simple.ini"
    echo "  -v, --verbose                          print verbose"
    echo "  -V, --version                          print version"
    echo "  -h, --help                             print this help message"
    echo
}

# chatbot.ini
CONFIG_TEMP=$(cat <<EOF
[uwsgi]
master = True
cheap = True
idle = 1800
die-on-idle = True # If app is not used often, it will exit and be launched
                   # again by systemd requested by users.
manage-script-name = True
chdir = <APP_PATH> # plz update this to match the path you want your app to locate
mount = /=<SCRIPT_NAME>:<FUNCTION_NAME> # plz update <SCRIPT_NAME> to match the script in the chdir directory
                                        # notice that the extension of the file is not needed E.G app.py => app
                                        # update <FUNCTION_NAME> to the uWSGI function. E.G. flask_app
EOF
)

debug() {
    if [[ $DEBUG -eq 1 ]];then
        if [[ ! -z $1 ]];then
            log debug "$1"
        else
            log debug "APPNAME    = $APPNAME"
            log debug "APPPATH    = $APPPATH"
            log debug "USER       = $USER"
            log debug "GROUP      = $GROUP"
            log debug "NUM        = $NUM"
            log debug "DEBUG      = $DEBUG"
            log debug "LOG        = $LOG"
            log debug "SERVICE    = $SERVICE"
            log debug "SUBOPTS    = $SUBOPTS"
            log debug "CONFIG_DIR = $CONFIG_DIR"
            log debug "WATCH      = $WATCH"
        fi
    fi
}

log() {
    printf " * \e[32m${0##*/}\e[0m:\e[36m$(date '+%H:%M:%S')\e[0m:\e[95m%-25s\e[0m$2\n" $1
    printf "\e[0m"
}

run() {
    if [ $DEBUG -ne 0 ];then
        log execute "$*"
    fi
    if ! command -v "${1%% *}" 2>&1 > /dev/null;then
        error "${1%% *} command not found"
    else
        $@ 2>&1 > /dev/null
    fi
    return $?
}

run_check() {
    if [[ $(id -u) -ne 0 ]];then
        error "This operation must run as root"
    elif ! command -v uwsgi 2>&1 > /dev/null;then
        error "uwsgi is not installed."
    fi
}

error() {
    log error "\e[31m$1\e[0m"
    exit 1
}

create() {
    if [[ ! -d $CONFIG_DIR ]];then
        run "mkdir -p $CONFIG_DIR"
    fi
    if [[ ! -d /etc/systemd/system/ ]];then
        error "Systemd config not found"
    fi
    if ! command -v nginx 2>&1 >/dev/null;then
        error "Nginx not found"
    fi
    debug "creating file to /etc/systemd/system/"
    debug "writing uwsgi-app@$APPNAME.service"
    printf "$SERVICER_TEMP\n" > $SERIVCE_FILE
    debug "writing uwsgi-app@$APPNAME.socket"
    printf "$SOCKET_TEMP\n" > $SOCKET_FILE
    debug "writing $APPNAME.ini to $CONFIG_DIR"
    if [[ -f $CONFIG_DIR/$APPNAME.ini ]];then
        log info "$CONFIG_DIR/$APPNAME.ini already exist."
        log input "do you want to override it? (y/n)"
        read -s -n1 yn
        while true;do
            if [[ $yn == 'y' ]];then
                printf "$INI\n" > $CONFIG_DIR/$APPNAME.ini
                break
            elif [[ $yn == 'n' ]];then
                log info "Will not override."
                break
            fi
            read -s -n1 yn
        done
    else
        printf "$INI\n" > $CONFIG_DIR/$APPNAME.ini
    fi
    run "systemctl daemon-reload"
    run "systemctl enable uwsgi-app@$APPNAME"
    run "systemctl enable uwsgi-app@$APPNAME.socket"
    update
    run "systemctl start uwsgi-app@$APPNAME"
    run "systemctl start uwsgi-app@$APPNAME.socket"
    run "systemctl reload nginx"
    log info "Created uwsgi-app@$APPNAME."
}

permission_check() {
    if [[ $(systemctl --all | grep uwsgi-app@$APPNAME | wc -l) -ne 2 ]];then
        error "Service uwsgi-app@$APPNAME not found"
    fi
    if ! run "id -u $USER";then
        error "User $USER not found."
    elif ! run "getent group $GROUP";then
        error "Group $GROUP not found."
    elif [[ ! -f $APPPATH ]];then
        if ! run "mkdir -p $APPPATH";then
            error "Cannot create $APPPATH"
        fi
    fi
}

# push changes to /opt/chatbot
update() {
    permission_check
    log info "updating $APPPATH"
    if run "rsync -r * $APPPATH";then
        if ! run "chown -R $USER:$GROUP $APPPATH";then
            error "Cannot change $APPPATH permission to $USER:$GROUP"
        fi
        if [[ $SERVICE -eq 3 ]];then
            log info "Restarting $APPNAME"
            run "systemctl restart uwsgi-app@$APPNAME"
        fi
    else
        error "Cannot sync current directory to $APPPATH"
    fi
}

remove() {
    permission_check
    log info "stopping all $APPNAME related service"
    if ! run "systemctl stop uwsgi-app@$APPNAME";then
        error "Cannot stop $APPNAME.service from running"
    fi
    if ! run "systemctl stop uwsgi-app@$APPNAME.socket";then
        error "Cannot stop $APPNAME.socket from running"
    fi
    log info "removing $APPNAME from service"
    if ! run "rm /etc/systemd/system/uwsgi-app@$APPNAME*";then
        error "Cannot remove systemd config for $APPNAME"
    fi
    log info "finding $APPPATH ..."
    if [[ -d $APPPATH ]];then
        log info "found $APPPATH"
        log info "start remove $APPPATH"
        if ! run "rm -r $APPPATH";then
            error "Cannot remove $APPPATH"
        fi
    fi
    log info "Reload systemd daemon"
    if ! run "systemctl daemon-reload";then
        error "something wrong with systemctl daemon reload"
    fi
    log info "$APPNAME service has been remove successfully."
}

manage() {
    if [[ -z $SUBOPTS || -z $APPNAME ]];then
        usage
        error "No Sub Option found."
    fi
    if [[ $(run "systemctl") -eq 0 || $(run "journalctl") -eq 0 ]];then
        case $SUBOPTS in
        start)
        run_check
        systemctl start uwsgi-app@$APPNAME
        ;;
        stop)
        run_check
        systemctl stop uwsgi-app@$APPNAME
        ;;
        restart)
        run_check
        systemctl restart uwsgi-app@$APPNAME
        ;;
        status)
        systemctl status uwsgi-app@$APPNAME
        ;;
        log)
        journalctl -u uwsgi-app@$APPNAME -b -n $NUM $WATCH
        ;;
        esac
    fi
}

main() {
    SERIVCE_FILE="/etc/systemd/system/uwsgi-app@$APPNAME.service"
    SOCKET_FILE="/etc/systemd/system/uwsgi-app@$APPNAME.socket"
    case $SERVICE in
    1)
    manage $@
    ;;
    2)
    create $@
    ;;
    3)
    update $@
    ;;
    4)
    remove $@
    ;;
    esac
}

if [[ "$(uname)" != "Linux" ]];then
    error "This script only can run under Linux environment with Systemd installed."
fi

while [[ $# -ne 0 ]];do
    case $1 in
    manage)
    shift
    SERVICE=1
    if [[ "$1" =~ start|stop|restart|log|status ]];then
        SUBOPTS=$1
        shift
    fi
    APPNAME=$1
    if [[ -z $SUBOPTS ]];then
        usage
        error "No sub option found."
    else
        shift
        for i in 1 2;do
            case $1 in
            -f)
            WATCH="-f"
            shift
            ;;
            -n)
            if [[ $2 =~ [0-9]+ ]];then
                shift
                NUM=$1
            else
                error "flag -n need a <arg:num> eg: -n 10"
            fi
            shift
            ;;
            esac
        done
    fi
    ;;
    create|update|remove)
    run_check
    SERVICE=$([[ $1 == 'remove' ]] && echo 4 || ([[ $1 == 'update' ]] && echo 3 || echo 2))
    shift
    APPNAME=$1
    APPPATH="/opt/$APPNAME"
    for i in 1 2 3;do
        case $2 in
        --ini)
        shift
        INI=$(cat $2)
        shift
        ;;
        -P|--path)
        shift
        PATH=$2
        shift
        ;;
        --permission)
        shift
        USER=$(echo $2 | cut -d: -f1)
        GROUP=$(echo $2 | cut -d: -f2)
        shift
        ;;
        esac
    done
    if [[ -z $INI ]];then
        if [[ ! -f "./uwsgi.conf.$APPNAME.ini" ]];then
            error "Cannot find ini file \"uwsgi.conf.$APPNAME.ini\""
        else
            INI=$(cat ./uwsgi.conf.$APPNAME.ini)
        fi
    fi
    ;;
    --generate-config)
    log "log" "create config to uwsgi.conf.sample.ini"
    printf "$CONFIG_TEMP\n" > uwsgi.conf.sample.ini
    exit
    ;;
    -V|--version)
    echo "${0##*/} v$VERSION"
    exit
    ;;
    -v|--verbose)
    DEBUG=1
    ;;
    -h|--help)
    usage
    exit
    ;;
    *)
    usage
    error "option $1 not found."
    ;;
    esac
    shift
done

debug

SERVICER_TEMP=$(cat <<EOF
[Unit]
Description=%%i uWSGI app
After=syslog.target
[Service]
ExecStart=$(command -v uwsgi) \
    --ini /etc/uwsgi/%%i.ini \
    --socket /var/run/uwsgid/%%i.socket
User=$USER
Group=$USER
Restart=on-failure
KillSignal=SIGQUIT
Type=notify
StandardError=syslog
NotifyAccess=all
EOF
)

SOCKET_TEMP=$(cat <<EOF
[Unit]
Description=Socket for uWSGI app %%i
[Socket]
ListenStream=/var/run/uwsgid/%%i.socket
SocketUser=$USER
SocketGroup=$USER
SocketMode=0660
[Install]
WantedBy=sockets.target
EOF
)

main