#include "ApplicationController.h"
#include "ApplyGrayscale.h"
#include "ApplyMonochrome.h"
#include "ApplyRotation.h"
#include "ApplyNegative.h"
#include "AddTransformationToImageInSessionCommand.h"
#include "MakeCollageCommand.h"
#include "AddImageToSession.h"
void ApplicationController::tokenize_string(const std::string &line) {
    std::istringstream check1(line);
    std::string intermediate;
    tokens.clear();
    while (check1 >> intermediate) {
        tokens.push_back(intermediate);
    }
    check1.str(std::string());//delete string stream
}
SessionCommandBase* ApplicationController::translate_tokens_to_command(const std::vector<std::string>& tokens) const {
	if (tokens[0] == "grayscale") {
		return new AddTransformationToImageInSessionCommand(this->active_, new ApplyGrayscale());
	} else if (tokens[0] == "monochrome") {
		return new AddTransformationToImageInSessionCommand(this->active_, new ApplyMonochrome());
	} else if (tokens[0] == "negative") {
		return new AddTransformationToImageInSessionCommand(this->active_, new ApplyNegative());
	} else if (tokens[0] == "rotate") {
		if (tokens.size() > 1) {
			bool is_clockwise = true;
			if (tokens[1] == "right") {
				is_clockwise = true;
				return new AddTransformationToImageInSessionCommand(this->active_,new ApplyRotation(true));
			} else if (tokens[1] == "left") {
				is_clockwise = false;
				return new AddTransformationToImageInSessionCommand(this->active_,new ApplyRotation(false));
			} else {
				throw std::invalid_argument("Rotate transformation should be either left or right.");
			}
		}
	} else if (tokens[0] == "add") {
		if (tokens.size() > 1) {
			return new AddImageToSession(this->active_, tokens[1]);
		} else {
			throw std::invalid_argument("Add command should be in the format: add <image file>");
		}
	} else if (tokens[0] == "collage") {
		if (tokens.size() == 5) {
			if (tokens[1] == "vertical") {
				return new MakeCollageCommand(this->active_, tokens[2], tokens[3], tokens[4],true);
			} else if (tokens[1] == "horizontal") {
				return new MakeCollageCommand(this->active_, tokens[2], tokens[3], tokens[4],false);
			}
			return nullptr;
		}
	}
	return nullptr;
}
void ApplicationController::saveSessionImages() {
    this->active_->applyAndPopTransformations();
    for (RasterImageBase* base : this->active_->raster_images_) {
        this->image_RW_.save(base, "");
    }
}
void ApplicationController::saveImageAs(const std::string &f) {
    if (this->active_->raster_images_.empty()) {
        throw std::invalid_argument("No images left in session!\n");
    } else {
        this->active_->raster_images_[0]->applyAndPopTransformations();
        this->image_RW_.save(this->active_->raster_images_[0], f);
        this->active_->popImageFirst();
    }

}
void ApplicationController::run() {
    std::string success_msg;
    bool flag = true;
    while (flag) {
        success_msg.clear();
        std::cout<<"Enter command:\n";
        std::getline(std::cin, line);

        tokenize_string(line);
        try {
            if (tokens.empty()) {
                continue;
            }
            if (tokens[0] == "save") {
                saveSessionImages();
            }
            else if (tokens[0] == "saveas") {
                if (tokens.size() == 2) {
                    saveImageAs(tokens[1]);
                }
            }
            else if (tokens[0] == "undo") {
                if (this->active_ != nullptr) {
                    if (!this->active_->command_stack_.empty()) {
                        SessionCommandBase* removed = this->active_->command_stack_.top();
                        removed->revert();
                        this->active_->command_stack_.pop();
                    } else {
                        throw std::invalid_argument("No commands to undo!\n");
                    }
                }
            } else if (tokens[0] == "info") {
                std::cout << this->active_->getInformation();
            } else if (tokens[0] == "exit") {
                flag = false;
            } else if (tokens[0] == "switch") {
                int new_id;
                new_id = std::stoi(tokens[1]);

                if (new_id > -1 && new_id < this->sessions_.size()) {
                    this->active_ = this->sessions_.at(new_id);
                    success_msg = "You switched to session with ID:" + std::to_string(new_id) + "!\n";
                } else {
                    throw std::out_of_range("Session Id does not exist!\n");
                }

            } else if (tokens[0] == "open") {
                RasterImageBase* img = RasterImageReader::read(tokens[1]);
                Session* s = new Session(img);
                s->setId(this->sessions_.size());
                this->sessions_.push_back(s);
                this->active_ = s;
                success_msg = "Session with ID:" + std::to_string(s->getId()) + " started \n"
                              + "Image \"" + img->getName() + "\" added \n";
            } else if (tokens[0] == "close") {
                if (this->active_) {
                    auto foundSes = std::find(this->sessions_.begin(), this->sessions_.end(), this->active_);
                    if (foundSes != this->sessions_.end()) {
                        this->sessions_.erase(foundSes);
                    }
                    int ses_id = active_->getId();
                    delete this->active_;
                    std::cout << "Closed session " << std::to_string(ses_id) << "\n";
                    if (this->sessions_.size() == 0) {
                        exit(0);
                    }
                    this->active_ = this->sessions_.front();
                }
            } else {
                SessionCommandBase* command = translate_tokens_to_command(tokens);
                if (command == nullptr) {
                    throw std::invalid_argument("Unrecognised command! \n");
                }
                command->execute();
                this->active_->command_stack_.push(command);
                success_msg = command->get_success_msg();
            }
        } catch (const std::exception& e) {

            std::cout << e.what();
        }
        std::cout << success_msg;
    }
}

ApplicationController &ApplicationController::getApplicationController() {
    static ApplicationController applicationController;
    return applicationController;
}

