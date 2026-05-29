#!/bin/bash

# git_push_config.sh - Script configurable

# === CONFIGURACIÓN ===
REPO_PATH="/home/optimus/Documentos/git/retroman"
BRANCH="main"
AUTO_PULL=true
AUTO_PUSH=true
SHOW_STATUS=true

# === FIN CONFIGURACIÓN ===

# Colores
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
RED='\033[0;31m'
NC='\033[0m'

# Cambiar al directorio del repo
cd "$REPO_PATH" || {
    echo -e "${RED}Error: No se encuentra $REPO_PATH${NC}"
    exit 1
}

# Obtener timestamp
TIMESTAMP=$(date '+%Y-%m-%d %H:%M:%S')
COMMIT_MSG="Update ${TIMESTAMP}"

echo -e "${YELLOW}📦 Repositorio: $(basename $REPO_PATH)${NC}"
echo -e "${YELLOW}🌿 Rama: $BRANCH${NC}"
echo -e "${YELLOW}📝 Mensaje: $COMMIT_MSG${NC}"

# Mostrar status
if [ "$SHOW_STATUS" = true ]; then
    echo ""
    git status --short
    echo ""
fi

# Verificar cambios
if git status --porcelain | grep -q .; then
    # Pull si está configurado
    if [ "$AUTO_PULL" = true ]; then
        echo -e "${YELLOW}🔄 Haciendo pull...${NC}"
        git pull origin $BRANCH --rebase
    fi
    
    # Agregar y commitear
    git add .
    git commit -m "$COMMIT_MSG"
    
    # Push si está configurado
    if [ "$AUTO_PUSH" = true ]; then
        echo -e "${YELLOW}🚀 Haciendo push...${NC}"
        git push origin $BRANCH
    fi
    
    echo -e "${GREEN}✅ Completado!${NC}"
else
    echo -e "${GREEN}✅ No hay cambios para subir${NC}"
fi
