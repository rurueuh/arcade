/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-arcade-lucas.mariette
** File description:
** SDL
*/

#include "SDL.hpp"
#include "signal.h"

void handle_signal(int signal)
{
    if (signal == SIGINT) {
        std::exit(0);
    }
}

SDL::SDL()
{
    signal(SIGINT, handle_signal);
    TTF_Init();
        _font = std::shared_ptr<TTF_Font>(TTF_OpenFont("./assets/font.ttf", 20), TTF_CloseFont);
    if (!_font.get()) {
        std::cerr << "Erreur : impossible de charger la police." << std::endl;
    }
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Erreur lors de l'initialisation de SDL : %s", SDL_GetError());
}
    createWindow();
    createRenderer();
}

SDL::~SDL()
{
    IMG_Quit();
    SDL_DestroyRenderer(_renderer.get());
    destroyWindow();
    // TTF_Quit();
    SDL_Quit();

}

void SDL::destroyWindow()
{
    SDL_DestroyWindow(_window.get());
}

void SDL::createWindow()
{
    _window = std::shared_ptr<SDL_Window>(SDL_CreateWindow("Arcade", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080, SDL_WINDOW_SHOWN), SDL_DestroyWindow);
}

void SDL::createRenderer()
{
    _renderer = std::shared_ptr<SDL_Renderer>(SDL_CreateRenderer(_window.get(), -1, SDL_RENDERER_ACCELERATED), SDL_DestroyRenderer);
}

void SDL::setAsset(std::map<char, std::string> asset)
{
    _asset = asset;
    loadAssets();
}

void SDL::setMap(std::vector<std::string> map)
{
    _map = map;
}

void SDL::draw()
{
    clearWindow();
    drawMap();
    SDL_RenderPresent(_renderer.get());
}

std::string SDL::getEvent()
{
    SDL_Event event = {0};

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                _isOpen = false;
                break;
            case SDL_WINDOWEVENT_CLOSE:
                _isOpen = false;
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT)
                    std::cout << "Tarhos Kovács ne se souvenait pas de grand-chose de son enfance, mais ce dont il se souvenait, il allait le pourchasser sa vie entière. Il se souvenait des cris et des hurlements dans le village. Il se souvenait de sa mère le forçant à ingurgiter un médicament ressemblant à un fluide noir et épais. Il se rappelait s’être écroulé sur le sol dur pour se réveiller dans une fosse commune, enterré sous une masse de corps, le bruit du village en feu lui emplissant les oreilles. Il se souvenait avoir poussé, tiré et escaladé la masse sanglante pour être finalement saisi par la mort, la destruction et le silence — le silence indifférent et impénétrable. Un son perçant résonna soudain dans ses oreilles et sa peau se mit à picoter lorsqu'il réalisa qu'il était en présence de quelque chose qui dépassait son entendement. Et bien qu'il n'ait pu exprimer ce qu'il éprouvait, il sut que ce n'était ni de la douleur, ni du chagrin, ni de la peur. C'était quelque chose d'autre. Quelque chose plus proche de —\n\nL'émerveillement.\n\nAlors que Tarhos s'efforçait de comprendre ce qui se passait, il ne remarqua pas les hommes qui s'approchaient derrière lui. Il ne réagit même pas lorsqu'ils l'emportèrent dans un chariot tiré par des chevaux et qu'ils l'enfermèrent dans une petite cage en bois en compagnie d'autres esclaves. Il demeura en contemplation devant la scène, fasciné. Et même alors qu'ils s'éloignaient en lui disant qu'il partait pour l'Italie, Tarhos regarda à travers les fentes du bois avec des yeux écarquillés et le cœur brûlant du désir de comprendre ce qui ne pouvait l'être.\n\nDepuis ce jour-là, Tarhos appartint à la Guardia Compagnia où il s'entraîna sous les ordres de Kadir Hakam. Là, il apprit à manier les armes, à forger des armures et à réciter un code de chevalerie pour servir avec obéissance ceux qui loueraient ses services. Au fil des années, Tarhos se fit peu d'amis parmi les mercenaires hostiles et compétitifs. Mais son talent, sa force et sa ruse attirèrent quelques acolytes persuadés que son courage leur portait chance au combat et qu'un jour il les aiderait à gagner leur liberté collective. Trois de ses acolytes lui jurèrent fidélité impérissable et en vinrent à être connus comme ses trois fidèles. Sa meute.\n\nAlejandro Santiago servait en tant qu'apprenti de l'armurier de la Guardia Compagnia.\n\nDurkos Malecek faisait preuve d'aptitudes pour la discrétion et les meurtres silencieux.\n\nSander Rault égalait Tarhos en taille et en force. Son arme de choix : une gigantesque hache de guerre.\n\nAlors que la Guardia Compagnia menait des campagnes dans des contrées reculées, Tarhos éliminait d'innombrables ennemis. Les années passèrent. Le sang coulait à flots. Et pourtant, toute cette tuerie ne rapprochait pas Tarhos de ce qu'il avait vécu dans son village. Néanmoins, pour sa valeur au combat, Tarhos fut adoubé chevalier et obtint sa liberté. L'esclave hongrois était désormais libéré, sa brutalité récompensée, bien que son cœur brûle toujours pour autre chose — quelque chose qu'il ne pouvait ni nommer ni décrire. Lassé de recevoir des ordres de ceux qu'il considérait comme ses inférieurs, Tarhos quitta la Guardia Compagnia pour se mettre à son compte. Leur chef, toutefois, refusa de laisser partir ses acolytes.\n\nDéterminé à gagner assez d'or pour libérer ses acolytes, Tarhos se fit employer par un riche seigneur italien. Vittorio Toscano était le duc de Portoscuro. C'était aussi un érudit, un voyageur ayant arpenté le monde, et un collectionneur de savoirs anciens dissimulés par une cabale inconnue de mystiques. Tarhos participa à la dernière expédition de Vittorio à la recherche d'un fragment d'un pilier provenant d'une ancienne école perdue dans le temps. Une pierre que Vittorio appelait le Lapis Paradisus, car il croyait qu'elle recelait des secrets pour ouvrir un portail vers un monde parfait par-delà bien et mal.\n\nL'expédition fouilla des ruines romaines en France et traversa les Pyrénées pour se rendre en Espagne où la piste mena aux catacombes sous la cité portugaise de Sintra.\n\nCes catacombes étaient considérées sacrées par les citoyens de la ville. Tarhos aurait à tuer les villageois montant la garde à l'entrée pour récupérer la pierre. Ne voulant pas déclencher un bain de sang, Vittorio ordonna à Tarhos de trouver un autre moyen. Mais Tarhos — qui avait assisté aux actes les plus affreux commis au nom de la chevalerie — refusa d'être dissuadé sous le prétexte de l'honneur. Il attendit que Vittorio reparte au camp à cheval. Puis, dans un puissant rugissement, il chargea et se tailla un chemin de tripes et de sang dans les ténèbres jusqu'à ce que la pierre soit entre ses mains.\n\nDe retour à la ville de Portoscuro, Tarhos emprisonna Vittorio dans son propre cachot, exigeant de connaître le sens des symboles gravés dans la pierre. Lorsque Vittorio refusa de parler, Tarhos tortura brutalement ses amis et ses parents et exhiba leurs corps de manière horrible dans les rues. Mais rien de ce qu'il fit n'ébranla la résolution de Vittorio qui garda le silence sur les secrets de la pierre. Fou de rage, Tarhos prit le contrôle des richesses de Vittorio et leva une petite armée. En quelques mois, Tarhos marcha sans crainte sur la Guardia Compagnia, décima leurs casernes, libéra ses acolytes, écrasa ses ennemis comme s'ils n'étaient rien et s'empara de leurs têtes de « moralisateurs » pour son étalage grandissant de « valeur ».\n\nAvec le temps, plusieurs seigneurs des provinces avoisinantes furent persuadés que Tarhos était l'incarnation du mal. Ils s'allièrent pour créer une armée « morale » et « vertueuse » afin de purger le mal de Portoscuro. Tarhos ignora leurs menaces. À ses yeux, les seigneurs n'étaient qu'un ramassis de lâches masquant leur ambition et leur avidité par des lois, des codes et des platitudes. Des lois et des codes et des platitudes conçus pour s'abriter des ténèbres mêmes auxquelles Tarhos s'abandonnait et qu'il acceptait sans jugement.\n\nMais, pendant que ses ennemis étaient en marche, Tarhos se rendit aux oubliettes pour infliger à Vittorio la mort qu'il méritait. Il refusait de lui accorder le moindre espoir de sauvetage. Animé d'intentions ténébreuses, il pénétra dans la petite prison, se fraya un chemin jusque dans les entrailles de la terre et remonta un couloir éclairé de torches. Il hésita un instant, réalisant qu'il n'apprendrait jamais le savoir et les secrets de Vittorio. Mais personne d'autre non plus. C'était satisfaisant à ses yeux. Et donc il déverrouilla la porte du cachot qu'il ouvrit d'un coup de pied. Deux enjambées rapides le menèrent dans une cellule vide à l'exception d'une infestation de rats.\n\nTarhos resta silencieux un moment, puis un rugissement d'indignation jaillit de ses poumons alors que la rumeur de la bataille résonnait soudain à travers la ville. Instantanément, il traversa le couloir en trébuchant, se rua dans les escaliers à vis, jaillit de la porte inondée de clair de lune et chargea au milieu de mares de viscères et de sang scintillant, écrasant et pulvérisant tous les ennemis sur son passage. Les seigneurs « moraux » et « vertueux » faisaient pleuvoir des boulets enflammés et des troncs d'arbre sur la ville, détruisant les foyers, écrasant les villageois comme des vers, défonçant le sol et embrasant des tas de foin et des stères de bois qui devenaient de gigantesques langues de feu.\n\nAu milieu du carnage et du chaos, la meute trouva Tarhos, et dos à dos, ils devinrent un tourbillon de mort. Certains crurent que leur courage leur portait chance. D'autres crurent que quelque chose de surnaturel les protégeait. Quoi que ce fut, ils terrassèrent à eux seuls des dizaines de guerriers aussi facilement que s'ils avaient écrasé des insectes à coup de pied. Et tandis qu'ils massacraient l'ennemi, Tarhos ne remarqua pas l'étrange brouillard se levant des cadavres et des armures qui s'entrechoquaient jusqu'à ce qu'il ne puisse plus voir à deux pas devant lui dans n'importe quelle direction.\n\nTarhos trébucha en avant, tâtonnant à travers l'épais brouillard semblable au fluide sombre que sa mère l'avait forcé à ingurgiter des années plus tôt. Sa coordination et son sens de l'orientation étaient bouleversés tandis qu'il appelait sa meute. Combien de temps erra-t-il dans les ténèbres presque parfaites, il ne le sut. Mais soudain le brouillard se dissipa pour révéler une fantasmatique terre ravagée de cadavres en décomposition et de villages en feu et de grandes tours en ruine, s'inclinant en vacillant à l'horizon. Il regarda, émerveillé. Un son perçant familier résonna dans ses oreilles, et sa peau se mit à picoter. Il se tint, subjugué, réalisant que par quelque incroyable chance son cœur avait trouvé exactement ce qu'il avait cherché toute sa vie durant. Il n'avait pas besoin de Vittorio. Il n'avait pas besoin de la pierre. Il avait trouvé son paradis. Il avait trouvé—\n\nLa beauté et l'horreur.\n\nIl avait trouvé -\n\nLe Sublime." << std::endl;
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    _isOpen = false;
                    break;
                }
                if (event.key.keysym.sym == SDLK_SPACE) {
                    return " ";
                }
                if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_q) {
                    return "Q";
                }
                if (event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_d) {
                    return "D";
                }
                if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_z) {
                    return "Z";
                }
                if (event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_s) {
                    return "S";
                }
                if (event.key.keysym.sym == SDLK_l) {
                    return "L";
                }
                if (event.key.keysym.sym == SDLK_m) {
                    return "M";
                }
                if (event.key.keysym.sym == SDLK_p) {
                    return "P";
                }
                if (event.key.keysym.sym == SDLK_i) {
                    return "I";
                }
                break;
        }
    }
    return "";
}

void SDL::loadAssets()
{
    for (auto &i : _asset) {
        std::shared_ptr<SDL_Texture> texture = std::shared_ptr<SDL_Texture>(IMG_LoadTexture(_renderer.get(), i.second.c_str()), SDL_DestroyTexture);
        _mapSprite[i.first] = texture;
    }
}

bool SDL::isOpen()
{
    return _isOpen;
}

void SDL::clearWindow()
{
    SDL_RenderClear(_renderer.get());
}

void SDL::drawMap()
{
    for (int x = 0; x < _map.size(); x++) {
        for (int y = 0; y < _map[x].size(); y++) {
            SDL_Rect rect = {y * 32, x * 32, 32, 32};
            SDL_RenderCopy(_renderer.get(), _mapSprite[_map[x][y]].get(), NULL, &rect);
        }
    }
}

void SDL::drawMenuGraphic(std::vector<std::pair<std::string, bool>> &menuGraphic)
{
    SDL_Color normalColor = {255, 255, 255}; // blanc
    SDL_Color highlightColor = {255, 0, 0}; // rouge

    for (int i = 0; i < menuGraphic.size(); i++) {
        std::string text = menuGraphic[i].first;
        bool highlight = menuGraphic[i].second;

        SDL_Color color = highlight ? highlightColor : normalColor;

        std::shared_ptr<SDL_Surface> textSurface(TTF_RenderText_Solid(_font.get(), text.c_str(), color), SDL_FreeSurface);
        if (!textSurface) {
            continue;
        }

        std::shared_ptr<SDL_Texture> texture(SDL_CreateTextureFromSurface(_renderer.get(), textSurface.get()), SDL_DestroyTexture);
        if (!texture) {
            continue;
        }

        int x = 10;
        int y = i * (20 + 10) + 10;
        SDL_Rect destRect = {x, y, textSurface->w, textSurface->h};
        SDL_RenderCopy(_renderer.get(), texture.get(), nullptr, &destRect);
    }
}

void SDL::drawMenuGames(std::vector<std::pair<std::string, bool>> &menuGames) {

    SDL_Color normalColor = {255, 255, 255};
    SDL_Color highlightColor = {255, 0, 0};

    int maxTextWidth = 0;
    for (int i = 0; i < menuGames.size(); i++) {
        std::string text = menuGames[i].first;
        int textWidth, textHeight;
        TTF_SizeText(_font.get(), text.c_str(), &textWidth, &textHeight);
        maxTextWidth = std::max(maxTextWidth, textWidth);
    }

    for (int i = 0; i < menuGames.size(); i++) {
        std::string text = menuGames[i].first;
        bool highlight = menuGames[i].second;

        SDL_Color color = highlight ? highlightColor : normalColor;

        // Définir la couleur du texte en fonction de la surbrillance

        std::shared_ptr<SDL_Surface> textSurface(TTF_RenderText_Solid(_font.get(), text.c_str(), color), SDL_FreeSurface);
        if (!textSurface) {
            continue;
        }

        std::shared_ptr<SDL_Texture> texture(SDL_CreateTextureFromSurface(_renderer.get(), textSurface.get()), SDL_DestroyTexture);
        if (!texture) {
            continue;
        }

        int x = 1920 - maxTextWidth - 20;
        int y = i * (20 + 10) + 10;
        SDL_Rect destRect = {x, y, textSurface->w, textSurface->h};
        SDL_RenderCopy(_renderer.get(), texture.get(), nullptr, &destRect);
    }
}


void SDL::drawMenu(std::vector<std::pair<std::string, bool>> &menuGraphic, std::vector<std::pair<std::string, bool>> &menuGames)
{
    clearWindow();
    drawMenuGraphic(menuGraphic);
    drawMenuGames(menuGames);
    SDL_RenderPresent(_renderer.get());
}


extern "C" std::shared_ptr<ILib> create()
{
    return std::make_shared<SDL>();
}
